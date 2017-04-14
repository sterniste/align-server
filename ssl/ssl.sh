#/bin/sh
openssl genrsa -des3 -out server.key 1024
openssl req -new -sha256 -key server.key -out server.csr
openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt
cp server.key server.key.secure
openssl rsa -in server.key.secure -out server.key
openssl dhparam -out dh512.pem 512

