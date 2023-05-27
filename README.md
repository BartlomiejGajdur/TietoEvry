
<h1  align="center">TietoEvry_cpp_task002</h1>

<h2  align="center"> More details, requirements and task description can be found in TietoEvry_cpp_task002.docx</h2>

How to run
  

      git clone https://github.com/BartlomiejGajdur/TietoEvry
      cd TietoEvry
      mkdir build
      cd build
      cmake ..
      make -j
      cd ..
      python .\TietoEvryGame.py File1.txt File2.txt File3.txt [TimeLimit]

How to run tests

     git clone https://github.com/BartlomiejGajdur/TietoEvry
     cd TietoEvry
     mkdir build
     cd build
     cmake ..
     make -j
     ./Tests.exe


File1.txt -> File that contains map structure.<br>
File2.txt -> Status file.<br>
File3.txt -> The file from which actions are loaded.<br>
TimeLimit -> Optional 

File1.txt ( It should contain at least the coordinates of the players' bases, i.e. the numbers 1 and 2)

    10006
    00029
    00000

File2.txt (Might be empty or should contain basic data)

    1      -> Number of Rounds
    P 2000 ->Money belongs to P
    E 2000 ->Money belongs to E
    ...
   File3.txt (Might be empty or contain actions to perform)
   

    0 B W   -> Base with id [0] try to start producing W [Worker]
    1 M 1 2 -> Unit with id [1] try to move to Coordinates{1,2}
    2 A 3   -> Unit with id [2] try to attack enemy unit with id [3]

