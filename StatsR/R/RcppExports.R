# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#' Retrieve descriptive statistics for a vector of values
#' 
#' @param data A vector of doubles.
#' @param keys An optional vector of keys.
#' @export
get_descriptive_statistics <- function(data, keys = as.character( c())) {
    .Call(`_StatsR_get_descriptive_statistics`, data, keys)
}

#' Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
#' 
#' @param xs A vector of doubles.
#' @param ys A vector of doubles.
#' @export
linear_regression <- function(xs, ys) {
    .Call(`_StatsR_linear_regression`, xs, ys)
}

#' Perform a t-test from summary input data
#' 
#' @param mu0 Population mean.
#' @param mean Sample mean.
#' @param sd Sample standard deviation.
#' @param n Sample size.
#' @export
t_test_summary_data <- function(mu0, mean, sd, n) {
    .Call(`_StatsR_t_test_summary_data`, mu0, mean, sd, n)
}

#' Perform a one-sample t-test
#' 
#' @param mu0 Population mean.
#' @param x1 A vector of doubles.
#' @export
t_test_one_sample <- function(mu0, x1) {
    .Call(`_StatsR_t_test_one_sample`, mu0, x1)
}

#' Perform a two-sample t-test
#' 
#' @param x1 A vector of doubles.
#' @param x2 A vector of doubles.
#' @export
t_test_two_sample <- function(x1, x2) {
    .Call(`_StatsR_t_test_two_sample`, x1, x2)
}

#' Perform a z-test from summary input data
#' 
#' @param mu0 Population mean.
#' @param mean Sample mean.
#' @param sd Sample standard deviation.
#' @param n Sample size.
#' @export
z_test_summary_data <- function(mu0, mean, sd, n) {
    .Call(`_StatsR_z_test_summary_data`, mu0, mean, sd, n)
}

#' Perform a one-sample z-test
#' 
#' @param mu0 Population mean.
#' @param x1 A vector of doubles.
#' @export
z_test_one_sample <- function(mu0, x1) {
    .Call(`_StatsR_z_test_one_sample`, mu0, x1)
}

#' Perform a two-sample z-test
#' 
#' @param x1 A vector of doubles.
#' @param x2 A vector of doubles.
#' @export
z_test_two_sample <- function(x1, x2) {
    .Call(`_StatsR_z_test_two_sample`, x1, x2)
}

#' Display the library name and version number.
#' 
#' @param 
#' @export
library_version <- function() {
    .Call(`_StatsR_library_version`)
}

#' Calculate a simple moving average
#' 
#' @param dates A vector of .
#' @param observations A vector of doubles.
#' @param window An integer representing the window size
#' @export
get_moving_average <- function(dates, observations, window) {
    .Call(`_StatsR_get_moving_average`, dates, observations, window)
}

