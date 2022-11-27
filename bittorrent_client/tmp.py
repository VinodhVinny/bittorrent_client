#!/usr/bin/python3

import hashlib

file = open("info_hash", "rb")
strn = file.read().decode(errors='replace')

hash_file = hashlib.sha1(strn.encode('utf-8'))
print(f"len: {len(str(strn))}")
print(f"hash: {hash_file.hexdigest()}")
