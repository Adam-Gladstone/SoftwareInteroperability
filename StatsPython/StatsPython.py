#!/usr/bin/env python

from Utilities import report_exception, print_results

import numpy as np
import pandas as pd
import inspect

import matplotlib.pyplot as plt

import StatsPythonPyBind as Stats
# import StatsPythonBoost as Stats


# DataManager
data_manager: Stats.DataManager = Stats.DataManager()

def introspect(obj):
    try:
        # Source code is not available
        # print(inspect.getsource(obj))
        for func in [type, id, dir, vars, callable]:
            print("%s(%s):\t\t%s" % (func.__name__, introspect.__code__.co_varnames[0], func(obj)))
    except Exception as inst:
        report_exception(inst)


def run_descriptive_statistics(data: list) -> None:
    """ Run descriptive statistics """
    try:
        summary: dict = Stats.DescriptiveStatistics(data)
        print_results(summary, "Descriptive Statistics")
    except Exception as inst:
        report_exception(inst)


def run_linear_regression(xs: list, ys: list) -> None:
    """ Run simple linear regression """
    try:
        lr: dict = Stats.LinearRegression(xs, ys)
        print(lr)
    except Exception as inst:
        report_exception(inst)


def run_moving_average() -> None:
    """ Check the simple moving average calculation """
    try:
        dates: list = list(range(1, 16))
        observations: list = [1, 3, 5, 7, 8, 18, 4, 1, 4, 3, 5, 7, 5, 6, 7]

        ma1: list = Stats.MovingAverage(dates, observations, 3)
        print(ma1)

        ts: Stats.TimeSeries = Stats.TimeSeries(dates, observations)
        ma2: list = ts.MovingAverage(3)
        print(ma2)

    except Exception as inst:
        report_exception(inst)


def run_statistical_tests1(df: pd.DataFrame) -> None:
    """ Run statistical tests """
    try:
        results: dict = Stats.SummaryDataTTest(5, 9.26146, 0.2278881e-01, 195)
        print_results(results, "Summary data t-test")

        # Perform the same test using the TTest class
        t0: Stats.TTest = Stats.TTest(5, 9.261460, 0.2278881e-01, 195)
        t0.Perform()
        print_results(t0.Results(), "Summary data t-test")

        # weight = [17.6, 20.6, 22.2, 15.3, 20.9, 21.0, 18.9, 18.9, 18.9, 18.2]
        weight: list = df.iloc[:, 0].tolist()

        results = Stats.OneSampleTTest(25, weight)
        print_results(results, "One-sample t-test")
        t1: Stats.TTest = Stats.TTest(25, weight)
        t1.Perform()
        print_results(t1.Results(), "One-sample t-test")
    except Exception as inst:
        report_exception(inst)


def run_statistical_tests2(df_x1: pd.DataFrame, df_x2: pd.DataFrame) -> None:
    """ Run more statistical tests """
    try:
        x1: list = df_x1.iloc[:, 0].tolist()
        x2: list = df_x2.iloc[:, 0].tolist()

        results: dict = Stats.TwoSampleTTest(x1, x2)
        print_results(results, "Two-sample t-test")

        t: Stats.TTest = Stats.TTest(x1, x2)
        t.Perform()
        print_results(t.Results(), "Two-sample t-test")
    except Exception as inst:
        report_exception(inst)


def ztest_summary_data() -> None:
    """ Perform a z-test from summary data """
    try:
        results: dict = Stats.SummaryDataZTest(5, 6.7, 7.1, 29)
        print_results(results, "Summary data z-test.")

        z: Stats.ZTest = Stats.ZTest(5, 6.7, 7.1, 29)
        z.Perform()
        print_results(z.Results(), "Summary data z-test.(class)")

    except Exception as inst:
        report_exception(inst)


def one_sample_ztest() -> None:
    """ Perform a one-sample z-test """
    try:
        data: list = [3, 7, 11, 0, 7, 0, 4, 5, 6, 2]
        results = Stats.OneSampleZTest(3.0, data)
        print_results(results, "One-sample z-test.")

        z: Stats.ZTest = Stats.ZTest(3.0, data)
        z.Perform()
        print_results(z.Results(), "One-sample z-test.(class)")

    except Exception as inst:
        report_exception(inst)


def two_sample_ztest() -> None:
    """ Run more statistical tests """
    try:
        x1: list = [7.8, 6.6, 6.5, 7.4, 7.3, 7.0, 6.4, 7.1, 6.7, 7.6, 6.8]
        x2: list = [4.5, 5.4, 6.1, 6.1, 5.4, 5.0, 4.1, 5.5]

        results: dict = Stats.TwoSampleZTest(x1, x2)
        print_results(results, "Two-sample z-test.")

        z: Stats.ZTest = Stats.ZTest(x1, x2)
        z.Perform()
        print_results(z.Results(), "Two-sample z-test.(class)")

    except Exception as inst:
        report_exception(inst)


def setup_data_manager() -> None:
    """ Define standard data sets used elsewhere """
    try:
        xs: list = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        ys: list = [1, 3, 2, 5, 7, 8, 8, 9, 10, 12]

        data_manager.Add("xs", xs)
        data_manager.Add("ys", ys)
        count: int = data_manager.CountDataSets()
        print("Number of datasets: " +  str(count))

        print(data_manager.__repr__)
    except Exception as inst:
        report_exception(inst)


if __name__ == "__main__":
    """ Exercise functions in the statistical library """
    setup_data_manager()

    xs: list = data_manager.GetDataSet("xs")
    ys: list = data_manager.GetDataSet("ys")

    run_descriptive_statistics(xs)
    run_linear_regression(xs, ys)

    filename: str = "../Data/weight.txt"

    # Read in data frame
    df: pd.DataFrame = pd.read_csv(filename, header=None)

    run_statistical_tests1(df)

    us_df: pd.DataFrame = pd.read_csv("../Data/us-mpg.txt", header=None)
    jp_df: pd.DataFrame = pd.read_csv("../Data/jp-mpg.txt", header=None)

    run_statistical_tests2(us_df, jp_df)

    print("Clearing up the datasets ...")
    print(data_manager.ListDataSets())
    data_manager.ClearDataSets()
    print("Number of datasets: " +  str(data_manager.CountDataSets()))

    #print(introspect(Stats.TTest))

    run_moving_average()

    ztest_summary_data()
    one_sample_ztest()
    two_sample_ztest()



