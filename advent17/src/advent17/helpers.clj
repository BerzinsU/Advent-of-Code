(ns advent17.helpers)

(defn int->digits [int]
  (->> int
       str
       (map (comp read-string str))
       vec))
