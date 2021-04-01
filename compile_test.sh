#!/bin/bash

nrnivmodl mechanism/
rm -rf scripts/x86_64
mv x86_64 scripts/
cd scripts/
python3 hpca_compartment.py

