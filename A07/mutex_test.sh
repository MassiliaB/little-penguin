#!/bin/bash

echo "Starting writes..."

echo "foo1" > /sys/kernel/debug/fortytwo/foo & 
sleep 0.1
echo "foo2" > /sys/kernel/debug/fortytwo/foo & 
wait
echo "Operations complete"
echo "Final content of foo"
cat /sys/kernel/debug/fortytwo/foo
