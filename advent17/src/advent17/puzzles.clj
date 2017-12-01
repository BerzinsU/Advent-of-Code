(ns advent17.puzzles
  (:require [advent17.helpers :as h]))

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