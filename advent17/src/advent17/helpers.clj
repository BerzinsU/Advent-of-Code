(ns advent17.helpers
  (:require [clojure.string :as str]))

(defn int->digits [int]
  (->> int
       str
       (map (comp read-string str))
       vec))

(defn calculate-row-checksum [row]
  (- (apply max row)
     (apply min row)))

(defn calculate-row-division-checksum [row]
  (reduce (fn [set digit]
            (let [filtered (first (filter #(and (not= digit %)
                                                (or (= (mod digit %) 0)
                                                    (= (mod % digit) 0))) row))]
              (if filtered
                [filtered digit]
                set)))
          (sort row)))

(defn calc-centered-octagonal-number [n]
  (+ (- (* 4 (* n n)) (* 4 n)) 1))

(defn centered-octagonal-number-seq
  ([] (centered-octagonal-number-seq 1 1))
  ([n number]
   (lazy-seq
     (cons number
           (centered-octagonal-number-seq
             (inc n)
             (calc-centered-octagonal-number (inc n)))))))

(defn generate-outward-spiral [length]
  (let [x 0
        y 0]
    ))

(defn validate-passphrase
  [passphrase]
  (let [split-passphrase (str/split passphrase #" ")]
    (= (count split-passphrase)
       (count (distinct split-passphrase)))))

(defn sort-words-by-chars [words]
  (mapv (fn [word]
          (-> word
              (str/split #"")
              sort
              str))
        words))

(defn validate-passphrase-anagram
  [passphrase]
  (let [split-passphrase (str/split passphrase #" ")]
    (= (count split-passphrase)
       (count (distinct (sort-words-by-chars split-passphrase))))))