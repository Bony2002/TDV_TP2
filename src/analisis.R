h1 <- c(ExperimentacionGapA$Valor.Objetivo.Heruistica.1)
h1_mean <- mean(h1)
h1b1 <- c(ExperimentacionGapA$Valor.Objetivo.Heuristica.1...Busqueda.Local.1)
h1b1_mean <- mean(h1b1)
h1b2 <- c(ExperimentacionGapA$Valor.Objetivo.Heuristica.1...Busqueda.Local.2)
h1b2_mean <- mean(h1b2)
mh1 <- c(ExperimentacionGapA$Metaheuristica1)
mh1_mean <- mean(mh1)

h2 <- c(ExperimentacionGapA$Valor.Objetivo.Heuristica.2)
h2_mean <- mean(h2)
h2b1 <- c(ExperimentacionGapA$Valor.Objetivo.Heuristica.2...Busqueda.Local.1)
h2b1_mean <- mean(h2b1)
h2b2 <- c(ExperimentacionGapA$Valor.Objetivo.Heuristica.2...Busqueda.Local.2)
h2b2_mean <- mean(h2b2)
mh2 <- c(ExperimentacionGapA$Metaheuristica2)
mh2_mean <- mean(mh2)

VO1 = c(h1_mean, h1b1_mean, h1b2_mean, mh1_mean)
VO2 = c(h2_mean, h2b1_mean, h2b2_mean, mh2_mean)

x = c("H","B1","B2","MH")
x_pos <- seq_along(x)

# Create an empty plot without x-axis
plot(x_pos, VO1, type = "n", xlab = "X-axis label", ylab = "Y-axis label", main = "Two Lines", xaxt = "n", xlim = c(1, length(x)), ylim = range(c(VO1, VO2)))

# Plot line 1
lines(x_pos, VO1, type = "l", col = "darkmagenta", lwd=2)

# Plot line 2
lines(x_pos, VO2, type = "l", col = "purple", lwd=2)

# Set x-axis tick positions and labels
axis(1, at = x_pos, labels = x)
