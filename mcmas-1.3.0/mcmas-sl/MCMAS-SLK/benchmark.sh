#!/bin/bash

for i in $(seq 3 18)
do
  echo "=== ${i} dining cryptographers ==="

  # ISPL file
  in_filename="examples/dining_cryptographers${i}.ispl"
  out_filename="examples/dining_cryptographers${i}.out"

  # Generate statistics
  ./mcmas ${in_filename} | tee ${out_filename}
done
