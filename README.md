# Music Reading Trainer

A console-based music reading training game designed to help users improve their ability to read musical notes on the staff. The game supports different tonalities, interactive keyboard input, note generation, and scoring to track progress through levels.

## Features

- Dynamic note generation with level progression
- Support for sharps and flats in key signatures
- Interactive keyboard highlighting based on pressed keys
- Score and level management with feedback on correct and incorrect answers
- Sound playback for pressed notes using **olcNoiseMaker.h** from [OneLoneCoder](https://github.com/OneLoneCoder/synth) 
- Modular design with test coverage for core components

## How to Play

Run the application and select a key signature to start practicing. Notes will appear on the staff, and you must identify and press the correct corresponding keyboard keys to score points and advance levels.

- At the start, select a key signature using the keyboard ("w" and "s" keys) and confirm by pressing **Enter**  
- Notes begin to appear on the staff from right to left  
- Guess the notes by pressing corresponding keys on your computer keyboard  
- Every **10 correct guesses**, a new note is added to the staff (increasing difficulty)  
- There are **16 levels** in total, each introducing new notes  
- The game tracks your score and updates your level based on performance  
- Press **ESC** at any time to reset the game and return to the key selection screen 

## Technologies

- C++ (console application)
- Unit testing with Microsoft Visual Studio C++ Unit Test Framework
