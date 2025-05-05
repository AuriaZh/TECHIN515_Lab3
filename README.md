# TECHIN515_Lab3

# Discussion
Play with your sorting hat. Are all 10 questions important to create the sorting hat? If you were to remove some questions to improve user experience, which questions would you remove and justify your answer.
- Not all 10 questions are equally important, some are mainly for fun and engagement. 

If you were to improve the sorting hat, what technical improvements would you make?
- “What do you value?”
- “How do your friends describe you?”
  
How could you improve the model's accuracy or efficiency?
- To improve accuracy, we could remove less relevant questions and focus on those that show greater variation across houses. Alternatively, we could add more distinct questions. Using a more lightweight model could also speed up predictions on the ESP32.

What additional sensors or hardware could enhance the user experience?
- Adding a voice module or some RGB LEDs would make the experience more interactive and magical.

Does decision tree remain suitable for your choice of new sensors? If yes, carefully justify your answer. If not, what ML model would you use and explain why.
- Given the limited input format (button presses), a decision tree still works well. But if we add continuous sensors later, a shallow neural network might be a better fit.

