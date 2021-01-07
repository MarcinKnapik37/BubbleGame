enum kolory{
    EMERALD,
    JADE,
    OBSIDIAN,
    PEARL,
    RUBY,
    TURQUOISE,
    BRASS,
    BRONZE,
    CHROME,
    COPPER,
    GOLD,
    SILVER,
    BLACK_PLASTIC,
    CYAN_PLASTIC,
    GREEN_PLASTIC,
    RED_PLASTIC,
    WHITE_PLASTIC,
    YELLOW_PLASTIC,
    BLACK_RUBBER,
    CYAN_RUBBER,
    GREEN_RUBBER,
    RED_RUBBER,
    WHITE_RUBBER,
    YELLOW_RUBBER,
};

std::vector< std::pair< std::vector< glm::vec3 >, float> > kolorki = {
    {{ glm::vec3(0.022, 0.175, 0.022),
       glm::vec3(0.076, 0.614, 0.076),
       glm::vec3(0.633, 0.728, 0.633)
    }, 76.800}, // emerald

    {{ glm::vec3(0.135, 0.222, 0.157),
       glm::vec3(0.540, 0.890, 0.630),
       glm::vec3(0.316, 0.316, 0.316)
    }, 12.800}, // jade

    {{ glm::vec3(0.054, 0.050, 0.066),
       glm::vec3(0.183, 0.170, 0.225),
       glm::vec3(0.333, 0.329, 0.346)
    }, 38.400}, // obsidian

    {{ glm::vec3(0.250, 0.207, 0.207),
       glm::vec3(1.000, 0.829, 0.829),
       glm::vec3(0.297, 0.297, 0.297)
    }, 11.264}, // pearl

    {{ glm::vec3(0.175, 0.012, 0.012),
       glm::vec3(0.614, 0.041, 0.041),
       glm::vec3(0.728, 0.627, 0.627)
    }, 76.800}, // ruby

    {{ glm::vec3(0.100, 0.187, 0.175),
       glm::vec3(0.396, 0.742, 0.691),
       glm::vec3(0.297, 0.308, 0.307)
    }, 12.800}, // turquoise

    {{ glm::vec3(0.329, 0.224, 0.027),
       glm::vec3(0.780, 0.569, 0.114),
       glm::vec3(0.992, 0.941, 0.808)
    }, 27.897}, // brass

    {{ glm::vec3(0.213, 0.127, 0.054),
       glm::vec3(0.714, 0.428, 0.181),
       glm::vec3(0.394, 0.272, 0.167)
    }, 25.600}, // bronze

    {{ glm::vec3(0.250, 0.250, 0.250),
       glm::vec3(0.400, 0.400, 0.400),
       glm::vec3(0.775, 0.775, 0.775)
    }, 76.800}, // chrome

    {{ glm::vec3(0.191, 0.073, 0.023),
       glm::vec3(0.704, 0.270, 0.083),
       glm::vec3(0.257, 0.138, 0.086)
    }, 12.800}, // copper

    {{ glm::vec3(0.247, 0.199, 0.075),
       glm::vec3(0.752, 0.606, 0.226),
       glm::vec3(0.628, 0.556, 0.366)
    }, 51.200}, // gold

    {{ glm::vec3(0.192, 0.192, 0.192),
       glm::vec3(0.508, 0.508, 0.508),
       glm::vec3(0.508, 0.508, 0.508)
    }, 51.200}, // silver

    {{ glm::vec3(0.000, 0.000, 0.000),
       glm::vec3(0.010, 0.010, 0.010),
       glm::vec3(0.500, 0.500, 0.500)
    }, 32.000}, // black_plastic

    {{ glm::vec3(0.000, 0.100, 0.060),
       glm::vec3(0.000, 0.510, 0.510),
       glm::vec3(0.502, 0.502, 0.502)
    }, 32.000}, // cyan_plastic

    {{ glm::vec3(0.000, 0.000, 0.000),
       glm::vec3(0.100, 0.350, 0.100),
       glm::vec3(0.450, 0.550, 0.450)
    }, 32.000}, // green_plastic

    {{ glm::vec3(0.000, 0.000, 0.000),
       glm::vec3(0.500, 0.000, 0.000),
       glm::vec3(0.700, 0.600, 0.600)
    }, 32.000}, // red_plastic

    {{ glm::vec3(0.000, 0.000, 0.000),
       glm::vec3(0.550, 0.550, 0.550),
       glm::vec3(0.700, 0.700, 0.700)
    }, 32.000}, // white_plastic

    {{ glm::vec3(0.000, 0.000, 0.000),
       glm::vec3(0.500, 0.500, 0.000),
       glm::vec3(0.600, 0.600, 0.500)
    }, 32.000}, // yellow_plastic

    {{ glm::vec3(0.020, 0.020, 0.020),
       glm::vec3(0.010, 0.010, 0.010),
       glm::vec3(0.400, 0.400, 0.400)
    }, 10.000}, // black_rubber

    {{ glm::vec3(0.000, 0.050, 0.050),
       glm::vec3(0.400, 0.500, 0.500),
       glm::vec3(0.040, 0.700, 0.700)
    }, 10.000}, // cyan_rubber

    {{ glm::vec3(0.000, 0.050, 0.000),
       glm::vec3(0.400, 0.500, 0.400),
       glm::vec3(0.040, 0.700, 0.040)
    }, 10.000}, // green_rubber

    {{ glm::vec3(0.050, 0.000, 0.000),
       glm::vec3(0.500, 0.400, 0.400),
       glm::vec3(0.700, 0.040, 0.040)
    }, 10.000}, // red_rubber

    {{ glm::vec3(0.050, 0.050, 0.050),
       glm::vec3(0.500, 0.500, 0.500),
       glm::vec3(0.700, 0.700, 0.700)
    }, 10.000}, // white_rubber

    {{ glm::vec3(0.050, 0.050, 0.000),
       glm::vec3(0.500, 0.500, 0.400),
       glm::vec3(0.700, 0.700, 0.040)
    }, 10.000}, // yellow_rubber
};
