# cs683_project

### <Project-Title>

### <Team-Name>

| **Member Name** | **Member Roll No.** |
| :-------------: | :-----------------: |
|  Priyansh Jain  |     210070063       |
| Priyanshu Gupta |     210070063       |
|  Chinmay Jadhav |     210070063       |

<br/>

---

### Proposal or Idea

The landscape of CPU system optimization revolves around the crucial role of cache efficiency in overall performance. Among the elements influencing this efficiency, the cache replacement policy stands out, directly impacting system effectiveness. Despite exhaustive exploration, devising an economical replacement strategy within hardware constraints remains a significant hurdle. Existing approaches like LRU and RRIP offer limited hardware impact but cater to specific access patterns, while recent methods incorporating program counter (PC) information show promise in adapting dynamically to changes in cache access. However, integrating PC into policies requires substantial hardware adjustments, creating a bottleneck in achieving adaptable yet hardware-efficient solutions.

To address this challenge, our proposal focuses on harnessing machine learning, particularly reinforcement learning (RL), to craft a cost-effective cache replacement policy. RL’s flexibility perfectly aligns with the cache replacement problem modeled as a Markov Decision Process. Leveraging insights from neural networks, our approach culminates in Reinforcement Learned Replacement (RLR), offering competitive performance without demanding extensive alterations to CPU microarchitecture. RLR aims to surpass traditional policies like LRU and DRRIP, promising adaptive cache replacement that responds dynamically to varying access patterns while remaining economically viable within hardware constraints.

<br/>

---

### Steps to run the experiments

```
$ ./config.sh <configuration file>
$ make
$ bin/champsim --warmup_instructions 200000000 --simulation_instructions 500000000 600.perlbench_s-210B.champsimtrace.xz
```

<br/>

---

### Conclusion

The evaluation results reveal compelling insights into cache replacement strategies, highlighting the impact of various factors on overall system performance. RD factor analysis demonstrates the significant influence of different factors on MPKI improvement and IPC speedup, with an optimal RD factor of 2 identified. Similarly, weighing age, hit, and type priorities reveals that adjusting these weights can substantially impact performance, with the (8,1,1) configuration emerging as the most effective. Notably, the findings indicate that altering age priority has a profound effect on speedup, whereas increasing hit rate priority shows less pronounced effects. Moreover, the comparison between RLR and LRU underscores RLR's superiority in achieving better overall performance. RLR's utilization of neural network-based learning, incorporating preuse distance predictions, access type considerations, hit history, and age-based priorities, presents a comprehensive and adaptable approach to cache replacement. The hardware implementation involves efficient mechanisms and multicore extensions, showcasing RLR's potential to significantly enhance cache performance across diverse workloads in modern computing systems.

<br/>

---

