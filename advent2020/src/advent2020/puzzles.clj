(ns advent2020.puzzles
  (:require [clojure.string :as str]
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

(defn read-inputs [path]
  (-> (slurp path)
      (str/split #"\n")
      (->>
        (map #(str/replace % #"\: | |\-" ";"))
        (map #(str/split % #"\;")))))


(defn day_2_1 []
  (time
    (let [inputs (read-inputs "inputs/input_day_2_1.txt")]
      (reduce (fn [counts password]
                (let [from (Integer/parseInt (first password))
                      to (Integer/parseInt (second password))
                      letter-char (-> password pop last char-array first)
                      char-counts (frequencies (last password))]
                  (if (and (contains? char-counts letter-char)
                           (<= from (char-counts letter-char) to))
                    (+ counts 1)
                    counts)))
              0
              inputs))))

(defn day_2_2 []
  (time
    (let [inputs (read-inputs "inputs/input_day_2_1.txt")]
      (reduce (fn [counts password]
                (let [index-1 (- (Integer/parseInt (first password)) 1)
                      index-2 (- (Integer/parseInt (second password)) 1)
                      letter-char (-> password pop last char-array first)
                      chars (-> password last char-array vec)
                      letter-in-first (= (chars index-1) letter-char)
                      letter-in-second (and (< index-2 (count chars))
                                            (= (chars index-2) letter-char))]
                  (if (and (or letter-in-first
                               letter-in-second)
                           (not (and letter-in-first
                                     letter-in-second)))
                    (+ counts 1)
                    counts)))
              0
              inputs))))