Utility for running some nmap scans given an input file of targets. Uses multithreading to quicken the process. This is not perfect code and is meant as an exercise in studying for the OSCP as well as learning C++.

```
.\rootrunner target_list
```

Executes the following nmap scans:
```
nmap -Pn -n -v -sT -A TARGET_IPS
nmap -Pn -n -v -sT -p- -T5 TARGET_IPS
nmap -Pn -n -sUV -p 53,67,68,69,123,137,138,161,162,500,514 TARGET_IPS
nmap -Pn -n -sC -sV TARGET_IPS
nmap -Pn -n --script=vuln -sT -A TARGET_IPS
```

Output:
```
TARGET_IP_1_output.txt
TARGET_IP_2_output.txt
...
```
