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
