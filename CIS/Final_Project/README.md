Code Structure: 
    
    The code uses no public libraries,everything is hand-written by me including the prime generation and big number math. I did all of the binary math using a class called "binary" which uses a string as a base. The class is imported as "binary.h" in the 3DES and RSA classes. The RSA and 3DES use .txt files in the unsecure_channel and local_storage to simulate actually sending,receiving, and storing keys and messages on two separate devices.

Binary.h: 

    Binary.h uses a string as it's base to represent binary numbers. Binary.h also overloads all basic operators (+,-,*...) to represent how they would work with binary numbers. AKA. + adds two binary numbers instead of concatenating them and so on. There are also several string functions that are overloaded since they are used in the encryption schemes like size() and append().

Prime generation: 

    I generate a random binary number of size n, divide it by the first 70 primes, and if it isn't divisible by them, I run 4 rounds of the rabin miller test (Found the number on Corpora.tika.apache.org, though it also recommended to do a lucas test and also said 5 tests now that I look again). My algorithm isn't the most efficient since my multiplication and division aren't optimized, but it works for the scale of the project. 
    
    Any size prime number can be generated, but I think a size of at least 100ish is necessary to send a 3DES key of 192 bits. 2 256 bit numbers takes 100+ seconds and I did 1024 bits and it took 6000 seconds. I know it's slow, but I don't know how slow in comparison to crypto++ functions (feel free to enlighten me if you know). I sent the 1024 bit primes with the project, just generate new ones if you actually want to do any math.

RSA.h:

    Runs RSA, don't use plain text larger than n-1 in size. Only use binary plaintext. Preface plain text with a ": " ("Plain Text: " is what the program uses by default).

3DES.h:

    Runs 3DES using 3 unique keys, any size message works. All unicode plain text works (except the null character since it's used to terminate extra, unwanted characters).

How to Run It:

    All the main functions to use are in order and commented out in the main file. However, there are also 2 encrypt_from_generation functions not included, one for each scheme, that you can use (The RSA one uses an int parameter for the size of the generated primes in bits). You can also declare an RSA object as RSA NAME(int) where the int is how large the primes should be in bits.

    ALL RSA PLAINTEXT IS BINARY. Any RSA plain text should be typed in advance in the .txt file (Or written to RSA from DES if you're using it as a hybrid scheme using the write_private_key_toRSA). Preface it  with a ": ", text behind the colon won't be read. 
    
    ALL 3DES UNICODE PLAINTEXT IS VALID. ALL 3DES plain text should exclude all characters but the plain text.

Short Comings and Improvements:

    First, I'd love to add a USER class that includes the RSA and 3DES classes so the user doesn't have to keep track of 2 objects when running the code as a hybrid scheme. Sadly I would only implement that once each class is fully finished, and I don't have the time to either. It's just far easier to test and debug when the classes are separate.

    Second, the local_storage folder is a little iffy since each user will overwrite the other users' data. This is fine for a hybrid scheme, outside 3DES private key since the end goal is for them both to be the same, but it still annoys me. It's a problem that wouldn't exist if it ran on 2 devices, but alas.

    Third, prime generation and binary math. Mainly, multiplication and likely division are very slow. I saw something called the karatsuba algorithm that would likely increase speed drastically. Also, I believe dividing by the first 300ish primes is more efficient than the first 70. However, I didn't have the time for either. Same for the Lucas mehtod mentioned earlier, but that's out of this project's scope anyways.

This is a bit more than a page, so thanks for reading!