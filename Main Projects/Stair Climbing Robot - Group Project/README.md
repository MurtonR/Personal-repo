# COMP208 Robot Scaling Vehicle Project

## Overview

This repository contains all the resources, code, and documentation for the COMP208 group project at Falmouth University (Second Year). The project involves designing and building a robot vehicle that can climb two flights of stairs (including a turn) and carry a 1kg cargo. 

<div style="display: flex; justify-content: space-between;">
  <img src="https://github.falmouth.ac.uk/GA-Undergrad-Student-Work-24-25/COMP208-GROUP-SCALING/blob/main/Media/Screenshots/stairs.png?raw=true" alt="Navigation" width="300">
  <img src="https://github.falmouth.ac.uk/GA-Undergrad-Student-Work-24-25/COMP208-GROUP-SCALING/blob/main/Media/Screenshots/1KG.png?raw=true" alt="Load Bearing" width="300">
  <img src="https://github.falmouth.ac.uk/GA-Undergrad-Student-Work-24-25/COMP208-GROUP-SCALING/blob/main/Media/Screenshots/locomotion.png?raw=true" alt="Locomotion" width="300">
</div>



- **Design and Manufacture:** Create a robot vehicle capable of climbing stairs and carrying cargo.
- **Documentation:** Use software tools to document the process, including:
  - CAD for design and prototyping
  - Arduino IDE for programming the robot's control system
- **Testing:** Implement testing to ensure the robot can perform tasks on flat surfaces and stairs.

### Team Members

- **Member 1:** [Anastasia Zaikina]
- **Member 2:** [Revan Murton]
- **Member 3:** [Luke Steppens]


### Repository Contents

- **CAD**
  - `Assemblies`: The complete robot assemblies.
  - `Parts`: Parts and components used in the design.
  - `Drawings`: Technical drawings of components and assemblies.
- **Code**
  - `Basic Component Code`: Code for individual components like motors and sensors.
  - `Control System`: The main code for controlling the robot's behavior.
  - `Test Code`: Scripts for testing individual components.
- **Documentation**
  - `Datasheets`: Technical specifications for used components.
  - `Design Documentation`: Detailed explanations of design decisions and iterations.
  - `Diagrams`: State Diagrams.
  - `Research`: Academic Papers and Grey Literature.
  - `Mathematics`: Notes Regarding gearing ratios.
- **Electronics**
  - `Schematics`: Circuit diagrams for wiring and connections.
  - `DataSheets`: Datasheets for electronic components.
- **Media**
  - `Photos`: Project Development and testing
  - `videos`: Project development and testing.
  - `Screenshots`: Used in delivery of posters, devlogs and github

  ### Code
The code in `scalingTurningStates` works on a simple 2 state system. One of the states is responsible for going forward and watching for walls when the robot is flat, and the other state watches for the robot being tilted, to continue climbing upwards.
![stateDiagram2](https://github.falmouth.ac.uk/GA-Undergrad-Student-Work-24-25/COMP208-GROUP-SCALING/assets/1907/11496b3b-43d4-46d5-a61d-550dc4b2cffc)

To alter `scalingTurningStates` to work in any new envinronment the following needs to be done:
- Check calibration of the Ultrasonic Sensor
- If readings dont match real life measurements, edit the code 
- The robot needs to have enough space to be able to turn 90 degrees in place, this is reflected in the variable `setDist` set at 43cm, change this if it needs more/less space
- Depending on the motors used the robot will turn at different speeds. If the robot doesn't reach the 90 degrees needed to turn, alter the delay in the function `turnRight90`.

  
 
  ### Research:

  This section contains a selection of our overall research, please refer to **Documentation** for further information. 
   
[1] S.-H. Chae, S.-M. Baek, J. Lee, and K.-J. Cho. Agile and energy-efficient jumping–crawling robot through rapid
transition of locomotion and enhanced jumping height adjustment. IEEE/ASME Transactions on Mechatronics,
27:5890–5901, Dec. 2022. https://ieeexplore.ieee.org/document/9842346.

[2] A. Pappalettera G. Reina and G. Mantriota. Design and analysis of tracked stair-climbing robot using innovative
suspension system. www.mdpi.com, 13:45, 2024/3. https://www.mdpi.com/2218-6581/13/3/45.

[3] T. Seo, S. Ryu, J. H. Won, Y. Kim, and H. S. Kim. Stair-climbing robots: A review on mechanism, sensing, and per-
formance evaluation. IEEE Access, 11:60539–60561, 2023. https://ieeexplore.ieee.org/stampPDF/getPDF.
jsp?arnumber=10154460.

[4] W Tao, J. Xu, and T. Liu. Electric-powered wheelchair with stair-climbing ability. International Journal of Advanced
Robotic Systems, 14:1729881417721436, 2017-07-01. https://doi.org/10.1177/1729881417721436.

[5] PrOjEcT TT. Converting motion ( linear to rotary 180 degrees ), Apr. 22 2020. Accessed: Dec. 16, 2024. [Online
Video]. Available: https://www.youtube.com/watch?v=U5osZB1y_p8.

[6] PrOjEcT TT. Converting motion ( linear to rotary 180 degrees ), Apr. 22 2020. Accessed: Dec. 16, 2024. [Online
Video]. Available: https://www.youtube.com/watch?v=U5osZB1y_p8.

[7] www.standard.co.uk. Fusion 360 tutorial: Gear and slider modeling. [Online Video]. Available:https://www.
youtube.com/watch?v=EmxC22lEbXY.

[8] J. Zhao Q. Yang Z. Zhang, B. Chang and X. Liu. Design, optimization, and experiment on a bioinspired jump-
ing robot with a six-bar leg mechanism based on jumping stability. Mathematical Problems in Engineering,
2020:3507203, 2020. https://onlinelibrary.wiley.com/doi/abs/10.1155/2020/3507203

[9]Adrénaline Amusements Team, Hungry hungry Hippos Operation & Service Manual, 2.0. Adrénaline Amusements. [Online]. Available: https://www.bandainamco-        am.co.uk/files/f/149639/x/6c75d13677/hungry_hungry_hippos_manual_v2.pdf

[10] DA Hofmann. Gearing for high speed motors. In IEE Colloquium on High Speed Bearings for Electrical Machines, pages 3–1. IET, 1997.

[11] Naoki Igo, Shota Yamaguchi, Noriyuki Kimura, Kazuma Ueda, Kenji Iseya, Kazuma Kobayashi, Toyoaki Tomura, Satoshi Mitsui, and Toshifumi Satake. Robots climbing up and down a steep stairs and robots retrieving objects from high places. Journal of Robotics and Mechatronics, 34(3):509–522, 2022.

[12] Ming-Shyan Wang and Yi-Ming Tu. Design and implementation of a stair-climbing robot. In 2008 IEEE Workshop on Advanced robotics and Its Social Impacts, pages 1–6. IEEE, 2008.

[13] Kan Yoneda, Yusuke Ota, and Shigeo Hirose. Stair climbing robots and high-grip crawler.

# Academic Papers - LS

## Academic Literature
[1] N. E. Anderson and R. W. Cedoz, “ADVANCED GEARBOX TECHNOLOGY FINAL REPORT”.

[2] P. S. Joshi, “Autonomous Stair Climbing Robot,” IJRASET, vol. 9, no. VII, pp. 2188–2203, Jul. 2021, doi: [10.22214/ijraset.2021.36816](https://doi.org/10.22214/ijraset.2021.36816).

[3] Y. Kim, J. Kim, H. S. Kim, and T. Seo, “Curved-Spoke Tri-Wheel Mechanism for Fast Stair-Climbing,” IEEE Access, vol. 7, pp. 173766–173773, 2019, doi: [10.1109/ACCESS.2019.2956163](https://doi.org/10.1109/ACCESS.2019.2956163).

[4] X. Gao, D. Cui, W. Guo, Y. Mu, and B. Li, “Dynamics and stability analysis on stairs climbing of wheel–track mobile robot,” International Journal of Advanced Robotic Systems, vol. 14, no. 4, p. 1729881417720783, Jul. 2017, doi: [10.1177/1729881417720783](https://doi.org/10.1177/1729881417720783).

[5] A. Kahraman, “Free torsional vibration characteristics of compound planetary gear sets,” Mechanism and Machine Theory, vol. 36, no. 8, pp. 953–971, Aug. 2001, doi: [10.1016/S0094-114X(01)00033-7](https://doi.org/10.1016/S0094-114X(01)00033-7).

[6] “Design Load Analysis and Optimization of Compound Epicyclic Gear Trains.” Accessed: Dec. 12, 2024. [Online]. Available: [https://www.researchgate.net/profile/Md-Raheem-Junaidi/publication/272490501_Design_Load_Analysis_and_Optimization_of_Compound_Epicyclic_Gear_Trains/links/54e61c230cf2cd2e028c6d50/Design-Load-Analysis-and-Optimization-of-Compound-Epicyclic-Gear-Trains.pdf](https://www.researchgate.net/profile/Md-Raheem-Junaidi/publication/272490501_Design_Load_Analysis_and_Optimization_of_Compound_Epicyclic_Gear_Trains/links/54e61c230cf2cd2e028c6d50/Design-Load-Analysis-and-Optimization-of-Compound-Epicyclic-Gear-Trains.pdf).

[7] “Optimal Design of Body Profile for Stable Stair Climbing Via Tri-wheels,” ResearchGate, Dec. 2024, doi: [10.1007/s12541-023-00887-4](https://doi.org/10.1007/s12541-023-00887-4).

[8] S. Qi, W. Lin, Z. Hong, H. Chen, and W. Zhang, “Perceptive Autonomous Stair Climbing for Quadrupedal Robots,” in 2021 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS), Sep. 2021, pp. 2313–2320. doi: [10.1109/IROS51168.2021.9636302](https://doi.org/10.1109/IROS51168.2021.9636302).

[9] L. Bonaiti, E. Knoll, M. Otto, C. Gorla, and K. Stahl, “The Effect of Sensor Integration on the Load Carrying Capacity of Gears,” Machines, vol. 10, no. 10, Art. no. 10, Oct. 2022, doi: [10.3390/machines10100888](https://doi.org/10.3390/machines10100888).

[10] A. Armillotta, “Tolerance analysis of gear trains by static analogy,” Mechanism and Machine Theory, vol. 135, pp. 65–80, May 2019, doi: [10.1016/j.mechmachtheory.2019.01.029](https://doi.org/10.1016/j.mechmachtheory.2019.01.029).

## Grey Literature
[1] “Compound Gears.” Accessed: Dec. 14, 2024. [Online]. Available: [https://technologystudent.com/gears1/gears3.htm](https://technologystudent.com/gears1/gears3.htm).

[2] Robot Design Engineering Lab, “Curved-Spoke Tri-Wheel Mechanism for Fast Stair-Climbing,” (Dec. 03, 2019). Accessed: Dec. 14, 2024. [Online Video]. Available: [https://www.youtube.com/watch?v=eB4nj6NUKVE](https://www.youtube.com/watch?v=eB4nj6NUKVE).

[3] “DIY Stair Climbing Robot,” STEMpedia Education. Accessed: Dec. 14, 2024. [Online]. Available: [https://ai.thestempedia.com/project/diy-stair-climbing-robot/](https://ai.thestempedia.com/project/diy-stair-climbing-robot/).

[4] “Gear Systems | KHK Gear Manufacturer.” Accessed: Dec. 14, 2024. [Online]. Available: [https://khkgears.net/new/gear_knowledge/gear_technical_reference/gear_systems.html](https://khkgears.net/new/gear_knowledge/gear_technical_reference/gear_systems.html).

[5] “How Does the Gearbox Function in Robots to Optimize Performance?” Accessed: Dec. 14, 2024. [Online]. Available: [https://www.zddriver.com/news/industry-news/how-does-the-gearbox-function-in-robots-to-optimize-performance.html](https://www.zddriver.com/news/industry-news/how-does-the-gearbox-function-in-robots-to-optimize-performance.html).

[6] “MIGO Ascender - The Stair-Climbing Robot Vacuum,” Kickstarter. Accessed: Dec. 14, 2024. [Online]. Available: [https://www.kickstarter.com/projects/migoascender/migo-ascender-the-stair-climbing-robot-vacuum](https://www.kickstarter.com/projects/migoascender/migo-ascender-the-stair-climbing-robot-vacuum).

[7] Jack Scalise, “Stair Climbing Robot - Quick Tips on Design Methodology, Engineering, and Dimensions,” (May 15, 2023). Accessed: Dec. 14, 2024. [Online Video]. Available: [https://www.youtube.com/watch?v=jw83jOphY8w](https://www.youtube.com/watch?v=jw83jOphY8w).

[8] DeeDeLogist, “Stair Climbing Robot - SM.mp4,” (Mar. 17, 2011). Accessed: Dec. 14, 2024. [Online Video]. Available: [https://www.youtube.com/watch?v=3qWYAOGZVM4](https://www.youtube.com/watch?v=3qWYAOGZVM4).

[9] “Stair-climbing Robot – Kikulab.” Accessed: Dec. 14, 2024. [Online]. Available: [https://www.kikulab.it-chiba.ac.jp/Eng/research/stair-climbing-robot/](https://www.kikulab.it-chiba.ac.jp/Eng/research/stair-climbing-robot/).

[10] “What is a Planetary Gear?” Accessed: Dec. 14, 2024. [Online]. Available: [https://www.regalrexnord.com/regal-rexnord-insights/what-is-a-planetary-gear](https://www.regalrexnord.com/regal-rexnord-insights/what-is-a-planetary-gear).



