(ns advent2020.puzzles
  (:require [advent2020.helpers :as h]
            [clojure.string :as str]))

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