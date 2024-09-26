# HumanSimulation
/!\ This project is under Construction /!\  
About this project I had a lot of ideas i count putting them to the github readme file
but for now there's a lot to do like: reinforcment intelligence, syncing with a clock the c++ and the python, creating emotions and actions for entity
I added a lot of new features to the projet, when I will finish debugging the main part, I will put a clear repo + instruction help and more.

# Main idea
The main idea is to create a simulation of humans and population.
Inspired by Conway's Game of Life, I'm trying to make an artificial simulation of all the behaviors a human (character) can have in a population.


# Exemple of 3D entity rendering using OpenGL
https://github.com/user-attachments/assets/28e5fc58-88b2-4121-bd8d-0b422cd757c0





# Detail
This project is still in beta and most things will be modified in the future. In order to create this simulation 
I have taken into account several development factors in 2 categories:
  - stats: stats are the basis of every character in this simulation, influencing their behavior, actions and everything else.
    They include: happiness, health, stress, anger, hygiene and much more.
  - emotion: emotions are temporary statistics that appear in different situations and also influence the actions and behavior of characters.
    e.g. sadness, illness, joy, depression and much more.

Just like humans, characters can reproduce (with a desire for emotion) between 2, we keep the genes of both parents and put them randomly into the child.
The child's behavior is also influenced by the parents' past experiences and actions.


I need to include a fast, true random algorithm (preferably in cpp) to make action and emotion happen, but also to take action.
Humans are pretty random so I need to create a randomness algorithm close to human randomness.

In addition, characters are also driven by an important rule, the quest for hapyness - all characters seek to improve their hapyness stats at 
every cost

# Update
I started working on an AI, for every entities. This ai will not be advanced and his model his close to machine learning (reinforcment intelligence more precisly) because of the fast and hug usage of ressources that could cause. At this point, the AI have some issues that I will fix, but this is not the most important. For now, optimization and adjustment on calculation and constant value need to be made. The more there is ticks and entities the more the simulation have trouble making it's job in time, that lead to some unexplicated behaviour, lags, bugs and sometimes crash (probably due to memory leak)

# Project
I may not finish this project entirely, it all came from an idea with a friend, but as a side project I could work on it. 
