# LEA

LEA is a 128-bit block cipher developed to provide confidentiality in high-speed environments such as big data and cloud computing, as well as lightweight environments such as IoT devices and mobile devices.

# Description

This project is to run LEA-128/196 on FPGA.
You can get the result of encryption/decryption by giving the key and plaintext/ciphertext.

# Requirements

- Xilinx PYNQ-Z1
- Vitis HLS 2020.2
- Vivado 2020.2
- Python 3.8.2
- pynqlinux v2.7
- Jupyter Notebook

# Install and Usage

- Download this repository
- Upload all the files under folder "LEA_files" to your PYNQ-Z1's Jupyter Notebook folder to implement this system
- Use jupyter notebook running on your PYNQ-Z1 and input key and plaintext/ciphertext, then execute.

## If you want to encrypt a sequence of numbers with LEA-128
```
key = np.array([0x3c2d1e0f, 0x78695a4b, 0xb4a59687, 0xf0e1d2c3])
plaintext = np.array([0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c])
```
# Author

- [Masahiro Shigekawa](https://github.com/ShigekawaMasahiro)

# References

- [ISO/IEC 29192-2:2019
Information security — Lightweight cryptography — Part 2: Block ciphers](https://www.iso.org/standard/78477.html)
- [K-subin/LEA: LEA Cipher Enc/Dec - GitHub](https://github.com/K-subin/LEA)

# License

- [MIT](https://opensource.org/licenses/MIT)
