#include <pgmspace.h>

#define SECRET
#define THINGNAME "omar_dev_board"                                       //change this

//const char WIFI_SSID[] = "DownTown-Guest";                                        //change this
//const char WIFI_PASSWORD[] = "lmdt@2022";      
const char WIFI_SSID[] = "Redmi Note 10 Pro";                                        //change this
const char WIFI_PASSWORD[] = "aaaaaaaa";   
//change this
//const char WIFI_SSID[] = "HUAWEI nova 5T";
//const char WIFI_PASSWORD[] = "monkeys123";
const char AWS_IOT_ENDPOINT[] = "a13d7wu4wem7v1-ats.iot.eu-west-1.amazonaws.com";        //change this

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVANX7stJprMxlgcisQg8JmOXgBu2cMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMTA1MTExMjU0
MzhaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQD6k7za7Bf+HkWJ4nFW
wNliRxBZ10RJ9f97jpxERoczzfhSW8TWFuk+WH1K7tGQBnZQSsD4YJapOBjUFdST
bnEAxHC2X8ArZItKQhhsXf0es9K0ISgFEVveblABvmTgJvV+d9P8SRBr3tHJTwad
6vQhounHoXXoFlothy4vO5i0/IL/wgG3HuCMespZLcKLEYQKvB1PQVMSHmw1AQ0P
OKblKuE0Va6jFhu1eHlBaT34rH7mTmKZ11pk2sVZu24mKYX5bhewyasnd28drHqV
C/DxuqYkCmISqYBHokFhXkTxjLd1QwXsiBZT/v8CuJCoBuoucd0e2qHtEOmX/oRR
zDM9AgMBAAGjYDBeMB8GA1UdIwQYMBaAFAgYhaugJ9fpiEbwgTWxsj0Zrky7MB0G
A1UdDgQWBBSi5La4YlOPqc753Fvhg9ufaqgqQzAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEApPi3Vok0N6CLVUE3ktUVnxyr
7mVz8rV42iWusFtAu/YS9FIxRuJOxaeungoqiPtHUKRp6M/hJzf5x4DUAQGP5eLf
EObU6t88t1DBYvHapf1/ZwhRJPzv3mmQZjFXuSEcqBFvi2bxgfFHVEHiNd9BFTk1
QREHgcAHsr2Ff4O5Jjko4pgaVEBKnaUCDWAjpzCODVMEZZzLZCELlum3xhYq0ef8
SddoE9AsRIHcdfh/r7lSnSSSYHEpfF2BrtMFBZFpk1vemU6/AjxQeLPt9VfWAsl9
uwqFkpQsQvqu433fGvByo735Ea2vc3Hr5H3Hp1muhRtaPU02MGyCjey+m6K8Bw==
-----END CERTIFICATE-----
)KEY";

// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA+pO82uwX/h5FieJxVsDZYkcQWddESfX/e46cREaHM834UlvE
1hbpPlh9Su7RkAZ2UErA+GCWqTgY1BXUk25xAMRwtl/AK2SLSkIYbF39HrPStCEo
BRFb3m5QAb5k4Cb1fnfT/EkQa97RyU8Gner0IaLpx6F16BZaLYcuLzuYtPyC/8IB
tx7gjHrKWS3CixGECrwdT0FTEh5sNQENDzim5SrhNFWuoxYbtXh5QWk9+Kx+5k5i
mddaZNrFWbtuJimF+W4XsMmrJ3dvHax6lQvw8bqmJApiEqmAR6JBYV5E8Yy3dUMF
7IgWU/7/AriQqAbqLnHdHtqh7RDpl/6EUcwzPQIDAQABAoIBAQCHkltBjy9D/Bjf
izaLG3gB5jUAhqmZ4pDBxtzhS89mxe+uj5wlwOudIb9YRXH4nKZytp9FQu0AzSsR
xGXpBn35Tk81PQT59UIvgSc5qniCngRIFRBT/ZpY9BIxf1OQu0Njk22MN/O8iSez
5R/NXQuND1mw+riSQ1WzAEqKn5H1iP8+huJlnxMca+JaIGHOpRKl/jry+oqTBXL0
9zKC9ltQYvw2VWY51HMebmJnvtJHDjWqEp+RJQPk62Q7Rs/7d1GVGsovsDigc4xf
TfZ4YizI08/w1qjMtxgoF6i4nG21TwCdOHlck1Ii8pFulTmpfkk0XdKSNB083nyy
rp3TLYyBAoGBAP1YudrZgGGjs4KnV3b1L+a3HTflhfSniyviORf20l9mewLBDCKR
qgbbX9djWvH5U2dfO/8RyedQfaaC72alUyBX8W42yHtbTDOUzu1uGitAckfdLz9F
g2hyjFJsXizi0/kMra7vQpnIjDxRjbLs+Hjsp+PKpXzNPLvKQIFhCyDNAoGBAP0z
lg7G2gZmXfdhpgndBNoyRfSqviT6ibxXngObIStVDi8ohZGPiG8bjfofFUGwPohB
dNOG3UHML2zZ+wkeVeB3MM0nRvE2HHDAvo0XhKwn8XNeTTYnq+nGnlawdi3KgPbO
3aKAP4+lelL6lpHJnKc2j9y1nMDZOJhcEGZ5ZpwxAoGBANTtQl9OWFk3xcK0tI01
a0oEctks3hYOzqhWXNfoSU2HCzH4YCOZu4ZB0F5tkd03SMLjxsANCl2QR9qvx1fE
8YWIhFC2WG9c/0GG+xeQZwwdAS+nFXOfD9+0Dn2juM8O4Us7Pap+SsKHTF3RyT8t
bXPsqvqHseifckD+rpJOppStAoGAAYO1ehEmbLNgDILBA34W8Vcro/MBgCcfe8jq
YQskf6Xal92eLui04DVB/CUDc4kiVp5NnJZJ7ILUJcqH/d34lYcg+5koi3jPYr1E
ZoOlf4Idp5sAyzohhRxzBgG4Mz3q148VNEugFbPfr29gRy71iOqCocdUULL7661h
S7ueKYECgYEAlhQcHFl7oqcvlnIFavRHZkL3c2/w8BycmxeCjRLosVLsfhU2ByQn
N+od4GUpM+mU82Qp2V8TgjbpB9fXmL0BwTUbcmcwR175wt6x4nq4l5KBt5aaGXlD
rNpPXYTS+VioCkFJ/hY+0Om43QlS3FD6OUj9vuFu1ep60TrYx6QdLak=
-----END RSA PRIVATE KEY-----

)KEY";