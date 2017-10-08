# huffman-file-compression
A personal project that falls within the course named "GLIN303 - Introduction aux systèmes et aux réseaux", taught under license 2 at the Faculty of Science of the University of Montpellier. 
### CODE RUNNING

- Compilation :

        gcc huffman_fonctions.c huffman_main.c huffman_fonctions.h -o huffman

- RUN
  *  From the executable
  
        ./huffman FILE OPTION  

          FILE: the file to compress/decompress

          OPTION: 1 to compress,  2 to decompress


  * From the Python script:
        
        ./huffman.py
### CONCEPTS
  huffman Algorithm

  C data struct (struct)
  
  binary operator

  Many concepts: files manipulation, arrays, basic concept of C language 

 ### NOTE:
 
  - Compression of these types of files work well:
  
         txt, mp3, jpg, jpeg

 - Compression of PDF file works too but file does not open ^^
 
  - Decompression also works but adds a mysterious character to the end of the file; which causes the txt, image and mp3 files to be edited at the end.
 
 
### AUTHOR

Abdoulaye DIALLO

       Group A

### TEACHER (s) 
  Pierre POMPIDOR

  marc MOULIS
### DATE
17 decembre 2013

