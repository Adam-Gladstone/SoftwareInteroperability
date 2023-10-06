###############################################################################
#
# Time Series
#
###############################################################################

library(zoo)                                       # Load zoo
library(StatsR)                                    # Native C++ stats library
library(Rcpp)

set.seed(98234)                                    # Creating example series

moving_average <- function(x, n = 5) {             # Create user-defined function
  stats::filter(x, rep(1 / n, n), sides = 1)
}

n = 100                                            # n samples
observations <- 1:n + rnorm(n = n, mean = 0, sd = 10)
dates <- c(1:n)

my_moving_average_1 <- StatsR::get_moving_average(dates, observations, 5)
my_moving_average_1

my_moving_average_2 <- moving_average(observations, 5)   # Apply user-defined function
my_moving_average_2 

tolerance = 1e-5
equal <- (my_moving_average_1 - my_moving_average_2) >= (tolerance - 0.5)
length(equal[TRUE])

my_moving_average_3 <- rollmean(observations, k = 5)  # Apply rollmean function
my_moving_average_3 

plot(1:length(observations), observations, type = "l",   # Plotting series & moving metrics
     ylim = c(min(observations), max(observations)),
     xlab = "Time Series", ylab = "Values")
lines(1:length(observations), my_moving_average_1, type = "l", col = 2)
legend("topleft", c("Time Series", "Moving Average"), lty = 1, col = 1:5)

moduleTS <- Module("TS", PACKAGE="StatsR")
ts <- new(moduleTS$TimeSeries, dates, observations)
my_moving_average_4 <- ts$MovingAverage(5)
my_moving_average_4

equal <- (my_moving_average_4 - my_moving_average_2) >= (tolerance - 0.5)
length(equal[TRUE])











