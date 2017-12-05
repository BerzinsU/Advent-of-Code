(ns advent17.puzzles
  (:require [advent17.helpers :as h]
            [clojure.string :as str]))

(defn inverse-captcha
  "http://adventofcode.com/2017/day/1"
  [int]
  (let [digits (h/int->digits int)
        looped-digits (conj digits (first digits))]
    (-> (reduce (fn [set digit]
                  (-> (if (= (:previous-digit set) digit)
                        (update set :sum + digit)
                        set)
                      (assoc :previous-digit digit)))
                {:sum 0}
                looped-digits)
        :sum)))

(defn halfway-captcha
  "http://adventofcode.com/2017/day/1"
  [int]
  (let [digits (h/int->digits int)
        count (count digits)
        halfway (/ count 2)]
    (-> (reduce (fn [set digit]
                  (let [halfway-index (mod (+ (:idx set) halfway) count)]
                    (-> (if (= digit (digits halfway-index))
                          (update set :sum + digit)
                          set)
                        (update :idx inc))))
                {:sum 0
                 :idx 0}
                digits)
        :sum)))

(defn corruption-checksum
  "https://adventofcode.com/2017/day/2"
  [spreadsheet]
  (->> spreadsheet
       (map h/calculate-row-checksum)
       (reduce +)))

(defn corruption-checksum-for-dividers
  "https://adventofcode.com/2017/day/2"
  [spreadsheet]
  (->> spreadsheet
       (map h/calculate-row-division-checksum)
       (reduce +)))

(defn validate-passphrase-list
  "https://adventofcode.com/2017/day/4"
  [passphrases]
  (count (filter #(h/validate-passphrase %) passphrases)))

(defn validate-passphrase-list-on-anagrams
  "https://adventofcode.com/2017/day/4"
  [passphrases]
  (count (filter #(h/validate-passphrase-anagram %) passphrases)))

(defn jump-out-of-list
  "https://adventofcode.com/2017/day/5"
  [list]
  (loop [steps 0
         idx 0
         list list]
    (if-let [step-value (get list idx)]
      (recur (inc steps)
             (+ idx step-value)
             (update list idx inc))
      steps)))

(defn jump-out-of-list-with-decrease
  "https://adventofcode.com/2017/day/5"
  [list]
  (loop [steps 0
         idx 0
         list list]
    (if-let [step-value (get list idx)]
      (recur (inc steps)
             (+ idx step-value)
             (update list idx (if (> step-value 2) dec inc)))
      steps)))