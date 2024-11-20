library(ggplot2)
library(tidyverse)

mandelbrot <- generate_mandelbrot(100, 100, 50, 
                            -1.5, 0.5, 
                            -1., 1.) #100, -1.5, 0.5, -1., 1.

mandelbrot_long <- mandelbrot |>
  as.data.frame() |> 
  mutate(y = n():1) |> 
  pivot_longer(cols = contains("V"),
                      names_to = "x",
                      values_to = "value") |>
  mutate(x = as.numeric(sub("V", "", x)))

(p <- ggplot(mandelbrot_long) +
  geom_tile(aes(x, y, fill = value)) +
  scale_fill_viridis_c(option = "turbo",
                       direction = -1
                       ) +
    theme(legend.position = "none",
          panel.grid = element_blank(),
          axis.title = element_blank(),
          axis.text = element_blank(),
          axis.ticks = element_blank(),
          panel.background = element_blank()))

ggsave("mandelbrot/mandelbrot_1.png",
       p,
       width = 40,
       height = 40)

julia <- generate_juliaset(
  -0.744, 0.148, # 0.285, 0.01, // −0.744 0.148 
  1000, 1000, 
  100, 
  -1.5, 1.5, 
  -1.5, 1.5) 

julia_l <- julia |>
  as.data.frame() |> 
  mutate(y = n():1) |> 
  pivot_longer(cols = contains("V"),
               names_to = "x",
               values_to = "value") |>
  mutate(x = as.numeric(sub("V", "", x)))

(p <- ggplot(julia_l) +
    geom_tile(aes(x, y, fill = value)) +
    scale_fill_viridis_c(option = "turbo", #"plasma",
                         direction = -1) +
    theme(legend.position = "none",
          panel.grid = element_blank(),
          axis.title = element_blank(),
          axis.text = element_blank(),
          axis.ticks = element_blank(),
          panel.background = element_blank()))

ggsave("mandelbrot/julia_5.png",
       p,
       width = 40,
       height = 40)
