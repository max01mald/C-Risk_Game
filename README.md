# C-Risk_Game

This is a C++ implemented game of Risk.

There are 16 Classes:
  
  Action Classes:
    Card:
      Type to determine the amount of Reinforcements 
    
    Hand:
      Determines which cards a player has access to
    
    Deck:
      Determines the distribution of cards to be used in the game
    
    Dice:
      Double Dice with random number generator 
    
  Structuring Classes:
    Map:
      Holds the different Continents and Countries in one Object
        
    Country:
      Determines the position of the Country on the map and its neighbours
      
    Continent:
      Determines the bonus Reinforcements to be allocated when a user owns one
      
    Filler: 
      Class which is tasked with IO to create the Country graph from a txt file
  
  Runtime Classes:
    Player:
      Determines the unique user and their progress in the game
    
    Start:
      Holds the Number of Players and the Directory of the Map to be used 
      
    Game:
      Holds the Start Class with an additional Name identifier so that multiple rounds can be          stored
      
    Tournament: Creates multiple games with pre-programmed player casts
  
  AI Classes:
    Human:
      Base Class which allows a user to play the game
      
    Aggressive:
      Pattern which creates a player which attacks while possible
  
    Benevolent: 
      Pattern which creates a player which never attacks
  
    Cheater:
      Pattern which creates a player which attacks, but allocates more Reinforcements than legal
  
