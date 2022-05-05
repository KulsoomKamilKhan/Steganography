# Who I am

- Name: Kulsoom Kamil Khan
- Student ID: H00333114
- Student username: kkk6

# Program design

**Structs** <br>
Three structs were created to support this program:

* typedef struct Pixel :
This struct holds the RGB values of a pixel. 

* typedef struct LL :
This is a nested struct that holds a char pointer to the first node of the linked list, and a struct pointer variable 'next'.

*  typedef struct PPM :
This struct contains width, height and maximum RGB value of the pixels, a pointer variable of struct Pixels, a char buff (array to read format of the P3 file), and the comment pointer of the Linked List.


**getPPMmethod**  <br>
This method is used to return a PPM image from the File fd. 
A PPM struct pointer is created and allocated with memory.

First, we check if the file is in 'P3' format by using an array to read the characters. If the characters being read are not in P3 format, an error message is printed.

Secondly, we check for comments in the file. Comments start with the character '#'. When this condition is true, we add them in the format of a linked list.
fseek is used to set the position in the file, i.e., move backwards one position from current(SEEK_CUR).
As we parse the comments, we malloc them into the linked list.
* The limitation for reading the comments is set at 100 characters.

The next thing we do, is parse and calculate the width and height of the image.

Lastly, we calculate the number of red, blue and green pixels in the ppm image.


**showPPM**  <br>
This method is used to print the information about the ppm images in the output file. Printf calls are used to display the format (P3), comments, width, height and pixel values of the ppm images.


**loadPPMFromFile**  <br>
This is a helper function that checks if the file can be loaded and returns it. It returns NULL or prints an error if the file is not in P3 format or cannot be found. It is called in the main method.


**encode**  <br>
The encode function hides the message text in the red pixels. We loop through the message text and generate random numbers. The numbers then replace the red value of the pixel with its appropriate ASCII character. After doing this, we return the image.


**decode**  <br>
In this function, we compare the original image with the new image to decode the message hidden. If the red pixel values in i2(new image) differ from i1(original image), it is converted into a character. The decoded message is then returned.


**main**  <br>
This is the main method that runs the steg program. 
* A dynamic memory allocation of 254 is given as the limitation for encoding the message text. <br>
text = malloc(sizeof(char) * 254);



# Choice of data structures and algorithms

The data structure primarily used in this program is **Linked List**, more specifically a singly linked list. <br>
The linked list implementation is advantageous in terms of dynamic memory allocation and due to the ease of insertion of nodes. <br>
The first instance of its use is in the getPPM() function where, the comments are parsed and stored in the linked list. The encode and decode functions were also written keeping in mind the linked list structure. The uniform use of this implementation ensured an easy implementation of the steg program.

