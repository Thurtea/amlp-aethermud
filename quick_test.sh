#!/bin/bash
# Quick test - create char and test one command

{
    sleep 0.5
    echo "quicktest2"
    sleep 0.5
    echo "test123456"
    sleep 0.5
    echo "test123456"
    sleep 1
    echo "1"
    sleep 1.5
    echo "yes"
    sleep 2
    echo "look"
    sleep 1
    echo "quit"
} | timeout 15 nc localhost 3000
