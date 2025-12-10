# Tamagotchi Moodeng 🦛

A virtual pet game inspired by the classic 1996 Tamagotchi, featuring Thailand's beloved pygmy hippo "Moo Deng" from Khao Kiew Open Zoo. Built on STM32F767ZI microcontroller as part of the Microcontroller Application Development course.

![Tamagotchi Moodeng](assets/preview.jpg)

## 📖 About

Tamagotchi Moodeng is an interactive embedded system project that simulates raising a virtual pet. Players care for Moo Deng by feeding, playing games, cleaning up, and ensuring proper rest. The pet's growth and survival depend on your care decisions, creating an engaging bond between player and character.

## ✨ Features

- **Interactive Pet Care System**
  - Feed with meals or snacks
  - Play mini-games to increase happiness
  - Clean up after your pet
  - Administer medicine when sick
  - Monitor sleep cycles with light detection

- **Evolution System**
  - Four life stages: Baby → Child → Teen → Adult
  - Growth influenced by care quality and player behavior

- **Game Mechanics**
  - Finite State Machine (FSM) architecture
  - Real-time stat tracking (Happiness, Hunger, Weight, Discipline)
  - Random events and status effects
  - Win/lose conditions based on pet health

- **Persistent Storage**
  - Game progress saved to Flash memory
  - Resume gameplay after power loss

## 🛠️ Hardware Components

| Component | Quantity | Description |
|-----------|----------|-------------|
| STM32F767ZI (NUCLEO-F767ZI) | 1 | Main microcontroller board |
| LCD ILI9341 2.8" TFT Display | 1 | 320×240 resolution, SPI interface |
| 3-Channel Push Button Module | 1 | Game controls (A, B, C buttons) |
| LDR Sensor Module | 1 | Light detection for sleep mode |
| Passive Buzzer | 1 | Sound effects and alerts |
| Custom Frame | 1 | Cardboard housing |

**Total Project Cost:** ~189 THB

## 🎮 Controls

- **Button A** - Back/Cancel or Scold (when pet is silly)
- **Button B** - Navigate menu or select left option
- **Button C** - Confirm action or select right option

## 📊 Game States

### Main States
1. **Idle/Status** - Display pet stats and select actions
2. **Meal** - Feed meals (+Hunger) or snacks (+Happiness)
3. **Mini Game** - Left/right guessing game
4. **Sleep** - Rest mode triggered by darkness (LDR sensor)
5. **CleanUp** - Remove waste to maintain health
6. **Medicine** - Cure sickness with treatment

### Pet Statistics
- **Happiness** (0-4) - Decreases over time, increased by playing/snacks
- **Hunger** (0-4) - Decreases over time, increased by feeding
- **Weight** (5-99) - Affects sickness probability and game success
- **Discipline** (0-6) - Affects feeding/playing success rates
- **Evolution Stage** (0-3) - Baby, Child, Teen, Adult

## 🏆 Win/Lose Conditions

**Win:** Reach adult stage (Evolution = 3) with full happiness (Happy = 4)

**Lose:** Happiness or Hunger reaches 0, causing the pet to die

## 🔧 Technical Implementation

### Software Architecture
- **Language:** C/C++
- **IDE:** STM32CubeIDE
- **Architecture:** Finite State Machine (FSM)
- **Display Driver:** ILI9341 SPI protocol
- **Storage:** Flash memory persistence
- **Peripherals:** ADC (LDR), PWM (Buzzer), GPIO (Buttons)

### Key Features
- DMA-optimized rendering
- Timer-based event system
- Probabilistic game mechanics
- Asset compression for 2MB Flash limitation

### Project Structure
```
.
├── Core/
│   ├── Inc/          # Header files
│   └── Src/          # Source files
├── Drivers/          # STM32 HAL drivers
├── Assets/           # Game graphics and sprites
└── README.md
```

## 📸 Screenshots

[Include screenshots of different game states here]

## 🚀 Getting Started

### Prerequisites
- STM32CubeIDE
- STM32F767ZI NUCLEO board
- Required hardware components (see Hardware Components section)

### Installation

1. Clone the repository
```bash
git clone https://github.com/CopperTrin/CE-Boostup-XII.git
cd CE-Boostup-XII
```

2. Open the project in STM32CubeIDE

3. Connect hardware components according to the wiring diagram in the documentation

4. Build and flash the program to your STM32 board

5. Power on and start caring for your Moo Deng!

## 📝 Hardware Connections

### LCD ILI9341 Pinout
- Connect SPI pins according to project schematic
- See documentation for detailed wiring diagram

### LDR Sensor
- Operating voltage: 3.3V-5V
- Analog output to ADC pin

### Passive Buzzer
- Operating voltage: 3.3V-5V
- PWM control pin

## 🐛 Known Issues & Limitations

1. **Flash Memory Constraints** - Limited to ~2 frames per animation due to 2MB Flash size
2. **Buzzer Blocking** - HAL_Delay() in music playback blocks other operations
3. **DMA Conflicts** - Cannot use DMA for ADC when rendering UI simultaneously
4. **Transparent PNG Handling** - Custom pixel-skipping required for transparency

## 📚 References

- [Tamagotchi (1996 Pet) - Fandom Wiki](https://tamagotchi.fandom.com/wiki/Tamagotchi_(1996_Pet))
- [Moo Deng - Wikipedia](https://en.wikipedia.org/wiki/Moo_Deng)
- [STM32F767ZI Documentation](https://www.st.com/en/microcontrollers-microprocessors/stm32f767zi.html)
- [ILI9341 Display Controller Datasheet](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf)

## 🙏 Acknowledgments

- Inspired by the original Tamagotchi (1996) by Bandai
- Special thanks to Moo Deng for being an internet sensation 🦛
- KMITL Computer Engineering Department

---
