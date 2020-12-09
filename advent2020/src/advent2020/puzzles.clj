(ns advent2020.puzzles
  (:require [clojure.string :as str]
            [clojure.set :as cs]
            [clojure.java.io :refer [resource]]
            [clojure.edn :as edn]))

(defn find-two-twenty [input]
  (time
    (let [smallNumbers (filter #(<= % 1010) input)]
      (filter int? (map (fn [small]
                          (reduce (fn [numbers number]
                                    (if (= (+ number small) 2020)
                                      (reduced (* number, small))
                                      numbers))
                                  []
                                  input))
                        smallNumbers)))))

(defn find-three-twenty [input]
  (time
    (let [smallNumbers (filter #(<= % 1010) input)]
      (map (fn [number]
             (let [rest (remove #(= % number) smallNumbers)]
               (map (fn [second]
                      (let [remaining (remove #(= % second) rest)]
                        (map (fn [third]
                               (if (= 2020 (+ number second third))
                                 (* number second third))) remaining)))
                    rest)))
           smallNumbers))))

(defn parse-inputs [[from to letter password]]
  {:from        (Integer/parseInt from)
   :to          (Integer/parseInt to)
   :letter-char (first letter)
   :password    password})

(defn read-inputs [path]
  (-> (slurp path)
      (str/split #"\n")
      (->>
        (map #(-> (str/split % #":*\s|-") parse-inputs)))))


(defn day_2_1 []
  (time
    (let [inputs (read-inputs "inputs/input_day_2_1.txt")]
      (reduce (fn [counts {:keys [from to letter-char password]}]
                (let
                  [char-counts (frequencies password)]
                  (if (and (contains? char-counts letter-char)
                           (<= from (char-counts letter-char) to))
                    (inc counts)
                    counts)))
              0
              inputs))))

(defn day_2_2 []
  (time
    (let [inputs (read-inputs "inputs/input_day_2_1.txt")]
      (reduce (fn [counts {:keys [from to letter-char password]}]
                (let [index-1 (dec from)
                      index-2 (dec to)
                      chars (-> password char-array vec)
                      letter-in-first? (= (chars index-1) letter-char)
                      letter-in-second? (and (< index-2 (count chars))
                                             (= (chars index-2) letter-char))]
                  (if (not= letter-in-first?
                            letter-in-second?)
                    (inc counts)
                    counts)))
              0
              inputs))))

;;Day 3
(defn read-inputs_3 [path]
  (-> (slurp path)
      (str/split #"\n")))


(defn plant-trees-to-right [forest right]
  (let [height (count forest)]
    (->> forest
         (map #(apply str (repeat (* right height) %)))
         (mapv #(str/split % #"")))))


(defn traverse [inputs right down]
  (reduce (fn [stepper row]
            (if (= (row (last stepper)) "#")
              [(inc (first stepper)) (+ (last stepper) right)]
              [(first stepper) (+ (last stepper) right)]))
          [0 right]
          (subvec (vec (take-nth down inputs)) 1)))


(defn day_3_1 []
  (time
    (let [right 3
          down 1
          forest (-> (read-inputs_3 "inputs/input_day_3_1.txt")
                     (plant-trees-to-right right))]
      (-> (traverse forest right down)
          first))))


(defn day_3_2 []
  (time
    (let [slopes [[1 1] [3 1] [5 1] [7 1] [1 2]]
          forest (-> (read-inputs_3 "inputs/input_day_3_1.txt")
                     (plant-trees-to-right 8))]
      (->> (map
             (fn [[right down]]
               (traverse forest right down))
             slopes)
           (map first)
           (reduce *)))))


;; Day 4

(defn parse-passports [raw]
  (->> (str/split raw #"\n\n")
       (map #(str/replace % #"\n" " "))
       (map (fn [line]
              (zipmap (->> (re-seq #"\w+(?=\:)" line)
                           (map keyword))
                      (re-seq #"(?<=:).*?(?=\s|$)" line))))))


(defn check-passports [passports]
  (let [parsed (parse-passports passports)
        allowed-keys #{:byr :iyr :eyr :hgt :hcl :ecl :pid}]
    (reduce (fn [has-req-fields passport]
              (let [diff (cs/difference allowed-keys (set (keys passport)))]
                (if (= (count diff) 0)
                  (conj has-req-fields passport)
                  has-req-fields)))
            [] parsed)))


(defn day_4_1 []
  (time
    (count (check-passports (slurp "inputs/input_day_4_1.txt")))))


(defn validate-passports [passports]
  (filter (fn [passport]
            (let [valid_bth (<= 1920 (Integer/parseInt (:byr passport)) 2002)
                  valid_iyr (<= 2010 (Integer/parseInt (:iyr passport)) 2020)
                  valid_eyr (<= 2020 (Integer/parseInt (:eyr passport)) 2030)
                  valid_hgt (if (= "cm" (re-find #"[a-zA-Z]+" (:hgt passport)))
                              (<= 150 (Integer/parseInt (re-find #"\d+" (:hgt passport))) 193)
                              (<= 59 (Integer/parseInt (re-find #"\d+" (:hgt passport))) 76))
                  valid_hcl (not (nil? (re-find #"\#[a-fA-F0-9]{6}" (:hcl passport))))
                  valid_ecl (not (nil? ((keyword (:ecl passport)) #{:amb :blu :brn :gry :grn :hzl :oth})))
                  valid_pid (not (nil? (re-find #"^\d{9}$" (:pid passport))))]
              (every? true? [valid_bth valid_iyr valid_eyr valid_hgt valid_hcl valid_ecl valid_pid])))
          passports))


(defn day_4_2 []
  (time
    (let [has-req-fields (check-passports (slurp "inputs/input_day_4_1.txt"))]
      (count (validate-passports has-req-fields)))))


;;Day 5

(defn read-input_lines [path]
  (-> (slurp path)
      (str/split #"\n")))


(defn midpoint [from to]
  (+ from (quot (- to from) 2)))


(defn calc-id [paths]
  (+ (* 8 (first paths))
     (last paths)))


(defn get_seat_id [seat-hash]
  (-> (reduce (fn [[from to left right] letter]
                (condp = letter
                  \F [from (midpoint from to) left right]
                  \B [(cond-> (midpoint from to) even? inc) to left right]
                  \R [from to (cond-> (midpoint left right) even? inc) right]
                  \L [from to left (midpoint left right)]))
              [0 127 0 7]
              seat-hash)
      calc-id))


(defn day_5_1 []
  (time
    (let [inputs (read-input_lines "inputs/input_day_5_1.txt")]
      (apply max (map get_seat_id inputs)))))


(defn day_5_2 []
  (time
    (let [inputs (read-input_lines "inputs/input_day_5_1.txt")
          ids (sort (map get_seat_id inputs))]
      (reduce (fn [last index]
                (if (not= (dec index) last)
                  (reduced (dec index))
                  index))
              (dec (first ids))
              ids))))


;; Day 6

(defn read-input_groups [path]
  (-> (slurp path)
      (str/split #"\n\n")))


(defn count-group-yes [group-answer]
  (->> (str/split group-answer #"\n")
       (map #(str/split % #""))
       (apply concat)
       set
       count))


(defn count-all-groups [answers]
  (reduce + (map count-group-yes answers)))


(defn day_6_1 []
  (time
    (let [inputs (read-input_groups "inputs/input_day_6_1.txt")]
      (count-all-groups inputs))))


(defn count-group-unanimous-yes [group-answer]
  (->> (str/split group-answer #"\n")
       (map #(str/split % #""))
       (map set)
       (apply cs/intersection)
       count))


(defn count-all-unanimous-groups [answers]
  (reduce + (map count-group-unanimous-yes answers)))


(defn day_6_2 []
  (time
    (let [inputs (read-input_groups "inputs/input_day_6_1.txt")]
      (count-all-unanimous-groups inputs))))


;;Day 7

(defn unpack_matroska [bags_inside]
  (->> (str/split bags_inside #" bag*\w+\, | bag*\w+\.")
       (mapv (fn [bag]
               (-> (str/replace bag #"\d+ " "")
                   (str/replace " " "_")
                   keyword)))))

(defn unpack [input child-unpack]
  (->> input
       (map #(str/split % #" bags contain "))
       (map (fn [[parent children]]
              {(keyword (str/replace parent " " "_")) (child-unpack children)}))))

(defn bags-containing [bags color]
  (let [parents (->> (filter #(contains? (-> % vals first set) color) bags)
                     (map #(keys %))
                     (apply concat)
                     set)]
    parents))

(defn bags-containing-multiple [bags colors]
  (->> colors
       (map #(bags-containing bags %))
       (apply concat)
       set))

(defn find-wrappings-bags [all-bags bag-ids]
  (loop [bag bag-ids
         found-colors bag-ids]
    (let [parents (bags-containing-multiple all-bags bag)]
      (if (< 0 (count parents))
        (recur parents (cs/union found-colors parents))
        (cs/union found-colors parents)))))

(defn count-wrapping-bags [all-bags]
  (dec (count (find-wrappings-bags all-bags #{:shiny_gold}))))

(defn day_7_1 []
  (time
    (let [all-bags (unpack (read-input_lines "inputs/input_day_7_1.txt") unpack_matroska)]
      (count-wrapping-bags all-bags))))

(defn unpack_matroska_with_counts [bags_inside]
  (->> (str/split bags_inside #" bag*\w+\, | bag*\w+\.")
       (mapv (fn [bag]
               (let [split (str/split bag #"(?<=\d) ")]
                 (if (= "no other" bag)
                   [:no_other 0]
                   [(keyword (str/replace (second split) " " "_")) (Integer/parseInt (first split))]))))))


(defn packer [all-bags start-bag counts]
  (let [bags (start-bag all-bags)
        values (map (fn [[bag-id bag-count]]
                      (let [return (* counts
                                      (if (= bag-count 0)
                                        0
                                        (packer all-bags bag-id bag-count)))]
                        return))
                    bags)]
    (+ (reduce + values) counts)))


(defn day_7_2 []
  (time
    (let [inputs (read-input_lines "inputs/input_day_7_1.txt")
          all-bags-counted (apply merge (unpack inputs unpack_matroska_with_counts))]
      (dec (packer all-bags-counted :shiny_gold 1)))))


;; Day 8

(defn split-operations [lines]
  (mapv (fn [line]
          (str/split line #" ")) lines))


(defn walk-the-stack [lines]
  (loop [stack lines
         index 0
         accum 0]
    (if (= (count stack) index)
      [accum true]
      (let [[opp amount] (stack index)]
        (if (= opp "visited")
          [accum (every? #(= "visited" %) stack)]
          (condp = opp
            "acc" (recur (assoc stack index ["visited"])
                         (inc index)
                         (+ accum (Integer/parseInt amount)))
            "jmp" (recur (assoc stack index ["visited"])
                         (+ index (Integer/parseInt amount))
                         accum)
            "nop" (recur (assoc stack index ["visited"])
                         (inc index)
                         accum)))))))


(defn day_8_1 []
  (time
    (let [input (-> (read-input_lines "inputs/input_day_8_1.txt")
                    split-operations)]
      (walk-the-stack input))))


(defn fix-the-stack [stack]
  (reduce (fn [idx [opp amount]]
            (let [new-opp (condp = opp
                            "nop" "jmp"
                            "jmp" "nop"
                            opp)
                  trial (walk-the-stack (assoc stack idx [new-opp amount]))]
              (if (second trial)
                (reduced trial)
                (inc idx))))
          0
          stack))


(defn day_8_2 []
  (time
    (let [input (-> (read-input_lines "inputs/input_day_8_1.txt")
                    split-operations)]
      (fix-the-stack input))))


; Day 9

(defn read-numbers [input]
  (mapv #(edn/read-string %) input))


(defn vec-remove
  [pos coll]
  (vec (concat (subvec coll 0 pos) (subvec coll (inc pos)))))


(defn can-sum? [sum list]
  (some true? (map-indexed (fn [idx number]
                             (some true? (map #(= sum (+ number %))
                                              (vec-remove idx list))))
                           list)))


(defn read-XMAS-weakness [p-length XMAS]
  (reduce (fn [[from to] number]
            (if (can-sum? number (subvec XMAS from to))
              [(inc from) (inc to)]
              (reduced number)))
          [0 p-length]
          (subvec XMAS p-length)))


(defn day_9_1 []
  (time
    (let [input (-> (read-input_lines "inputs/input_day_9_1.txt")
                    read-numbers)]
      (read-XMAS-weakness 25 input))))


(defn search-summers [sum list]
  (->> (map-indexed (fn [idx number]
                      (reduce (fn [[acc numbers] number]
                                (let [new-sum (+ acc number)
                                      new-numbers (conj numbers number)]
                                  (cond
                                    (or (= number sum)
                                        (< sum new-sum)) (reduced nil)
                                    (= sum new-sum) (reduced new-numbers)
                                    :else [new-sum new-numbers])))
                              [0 []]
                              (subvec list idx)))
                    list)
       (remove nil?)
       (apply into [])))


(defn exploit-XMAS-weakness [entry XMAS]
  (let [summers (search-summers entry XMAS)]
    (+ (apply min summers) (apply max summers))))


(defn day_9_2 []
  (time
    (let [input (-> (read-input_lines "inputs/input_day_9_1.txt")
                    read-numbers)
          weak-point (read-XMAS-weakness 25 input)]
      (exploit-XMAS-weakness weak-point input))))
