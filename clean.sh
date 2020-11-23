#!/bin/bash
find . -type f  ! -name "*.*" -depth 1  -delete
find . -type f  -name "*.out" -depth 1 -delete
find . -type f -name "*.exe" -depth 1 -delete

