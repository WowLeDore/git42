#!/bin/bash
ifconfig -a | grep ether | cut -c 15-31
