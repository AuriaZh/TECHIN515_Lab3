# TECHIN515_Lab3

# Discussion
Play with your sorting hat. Are all 10 questions important to create the sorting hat? If you were to remove some questions to improve user experience, which questions would you remove and justify your answer.
- Some questions are mainly there for engagement and fun. For example, “What do you value?” and “How do your friends describe you?” seem to overlap and might not both be needed.
- I'd remove questions with similar meanings and keep ones that show clearer differences between house types. Or, add more diverse questions to make the sorting more accurate.

If you were to improve the sorting hat, what technical improvements would you make?
- I would make the sorting hat more interactive and polished. For example, I’d add a loading animation during prediction, improve the button debounce logic, and maybe integrate touch input instead of physical buttons. I’d also optimize memory usage and reduce boot-up time for a smoother experience.
  
How could you improve the model's accuracy or efficiency?
- To improve accuracy, we could remove less relevant questions and focus on those that show greater variation across houses. Alternatively, we could add more distinct questions. Using a more lightweight model could also speed up predictions on the ESP32.

What additional sensors or hardware could enhance the user experience?
- Adding a voice module or some RGB LEDs would make the experience more interactive and magical.

Does decision tree remain suitable for your choice of new sensors? If yes, carefully justify your answer. If not, what ML model would you use and explain why.
- Given the limited input format (button presses), a decision tree still works well. But if we add continuous sensors later, a shallow neural network might be a better fit.

