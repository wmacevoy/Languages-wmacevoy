#!/bin/bash
docker build -t shift_reduce_calc . && docker run --rm shift_reduce_calc ./calc "$@"
