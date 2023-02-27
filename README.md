# GaTher3DEvo

Program2.c can be used to calculate the outcome of evolutionary game theory's payoff matrix, while GUI.py to visualize that outcome.

An XML file of the structure defined similarly to what is shown below is needed as an input to both programs:
```
<?xml version="1.0" encoding="UTF-8"?>
<data>
    <inputs> 
        <dimension>2</dimension><!--dimensions-->
        <size>10</size><!--size of input matrix-->
        <MSEG>0</MSEG><!--0 - spatial games; 1 - mixed games-->
        <maxgeneration>500</maxgeneration> <!--number of generations-->
        <mortality>0.1</mortality> <!--mortality, for semi-synchronous updating method only-->
        <updating>1</updating><!--0 - asynchronous;
                1 - semi-synchronous; 2 - synchronous-->
        <neighbourhooud>0</neighbourhood> <!--0 - von Neumann neighbourhood; 
                1 - Moore neighbourhood-->
        <reproduction>2</reproduction><!--0 - probabilistic;
                1 - deterministic; 2 - weighted mean-->
        <param>3</param><!--number of cells for mean, for weighted mean reproduction method only-->
       <resources v="6" c="9" param1="0.0" param2="1.0"
        param3="300">step</resources><!--resources function-->
        <payoff>
            <row r="0">2 1.5 4</row>
            <row r="1">3 1 0</row>
            <row r="2">3 1 3</row>
        </payoff><!--payoff matrix-->
        <init-population>binFile</init-population><!--bin matrix with initial population;
        if missing, initial population is randomized-->
    </inputs>
    <outputs>
        <save-path>outputFile</save-path><!--save path-->
    </outputs>
</data>
```

Initial population matrix is a bin matrix - for 3x3 game lattice for 2 phenotypes, its size is 3x3x2 (3x3 for one phenotype and 3x3 for the other, subsequently).

In order to use the graphic user interface, an input XML file must be provided, and the file path can be specified
in two different ways, either by writing a Python program call and GUI file name into the terminal, after which the
user will be asked to provide file path to XML file, or adding it after GUI file name.

GUI allows user to see average result of all generations, time course of phenotypes and 3D results for given generation.

Software written by Marek Bonk as part of his Master's Thesis project on Silesian University of Technology.
