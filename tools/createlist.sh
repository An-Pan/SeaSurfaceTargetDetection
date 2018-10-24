#!/bin/bash
(ls -1 |awk '{print i$0}' i=`pwd`'/') >> list.txt
