
# Neural Network

This is a machine learning project built entirely from scatch in C++. A neural network is trained to drive cars through an obstacle course drawn by the user in real-time. The network gradually evolves through each generation, naturally tuning its configuration for more efficient navigation.

The graphical display is implemented using SFML.
## Installation

Install by cloning the repo and setting up the Visual Studio project

```bash
  git clone https://github.com/MichaelCASC5/NeuralNetwork.git
```
    
## Optimizations

The project is now multi-threaded, where the graphical screen drawing and the game logic happens in their own threads; each is soley responsible for their respective work.

The collision detection algorithm and behavior has been improved as the cars no longer die upon collision, but have a chance to turn away and continue searching for solutions.

Functionalities like propagation and normalization are implemented by focusing on separation of concerns. The project is designed to be modular and built for scalability. The main driver, the car simulation, and the neural network are distinct projects within the VS solution.
## Features

- Real-time graphical display
- User can draw obstacles on the screen
- Resolution of simulation can be specified
## Roadmap

- Better graphics for easier communication of technical ideas

- Improve the genetic algorithm to allow a specified mutation percentage rate

- Force the networks to be more competitive and find better solutions

- Allow for sexual reproduction rather than asexual cloning of the most fit

- Allow for different lineages of networks for greater genetic diversity

- Build an executable program




## Lessons Learned

Neural networks are lazy. The engineer must be very careful to design the network's training algorithm in a way that ensures the level of complexity to be accomplished in the network. As I have seen, the networks don't necessarily find the best solutions, just the ones that take the least amount of cognitive effort to reach.


## Authors

- [@MichaelCASC5](https://github.com/MichaelCASC5)
- [@Allimonae](https://github.com/Allimonae)



## Support

For support or feedback, email michaelcalle14@gmail.com

## Related

This project is a sequel to my previous AIracers project, which uses a different machine learning algorithm of my own invention. It can be found here:

- [AIracers](https://github.com/MichaelCASC5/AIracers)
