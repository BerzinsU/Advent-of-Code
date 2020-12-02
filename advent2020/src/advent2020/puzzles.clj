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