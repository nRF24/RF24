#!/bin/sh

# Connect u0 to receiver, u0 to sender
# WARNING: Test config 2 only works with PLUS units.

jam u0 u1 && expect test.ex 1
jam u0 u1 && expect test.ex 2
jam u0 u1 && expect test.ex 3
