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

(defn already-in-history? [history item]
  (not (empty? (filter #(= % item) history))))

(defn next-step-in-memory [memory current-idx]
  (mod (inc current-idx) (count memory)))

(defn reallocate-memory [memory-blocks]
  (let [max (apply max memory-blocks)
        index-of-max (first (keep-indexed #(when (= max %2) %1) memory-blocks))]
    (loop [blocks-to-reallocate max
           idx (next-step-in-memory memory-blocks index-of-max)
           memory (assoc memory-blocks index-of-max 0)]
      (if (= 0 blocks-to-reallocate)
        memory
        (recur (dec blocks-to-reallocate)
               (next-step-in-memory memory-blocks idx)
               (update memory idx inc))))))