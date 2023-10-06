#pragma once

#ifdef DYNAMIC
#   ifdef STATSDLL_EXPORTS
#       define STATSDLL_API __declspec(dllexport)
#   else
#       define STATSDLL_API __declspec(dllimport)
#   endif
#else
#   define STATSDLL_API
#endif

#ifdef _MSC_VER
	#pragma warning( disable: 4251 ) // warning C4251: 'stl': class '...' needs to have dll-interface to be used by clients of class '...'
#endif

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

namespace StatisticsLibrary
{
    // Base class for statistical testing: tTest, zTest, fTest ...
    class STATSDLL_API StatisticalTest
    {
    public:
        // Construction
        StatisticalTest() = default;

        // Destructor
        virtual ~StatisticalTest() = default;

        // Perform the statistical test
        virtual bool Perform() = 0;

        // Retrieve the results
        [[nodiscard]]
        std::unordered_map<std::string, double> Results() const;

        // Move constructor   
        StatisticalTest(StatisticalTest&& other) = default;

        // Move assignment operator   
        StatisticalTest& operator=(StatisticalTest&& other) = default;

        // Copy constructor   
        StatisticalTest(const StatisticalTest& other) = default;

        // Copy assignment operator   
        StatisticalTest& operator=(const StatisticalTest& other) = default;

    protected:
        // Collection of named results
        std::unordered_map<std::string, double> m_results;
    };

    // T-Test
    class STATSDLL_API TTest final : public StatisticalTest
    {
        enum class STATSDLL_API TestType { Unknown, OneSample, TwoSample, NoSample };

    public:
        // Summary data: population mean, sample mean, sample standard deviation, sample size.
        TTest(double mu0, double x_bar, double sx, double n);

        // One-sample: population mean, sample.
        TTest(double mu0, std::vector<double> x1);

        // Two-sample
        TTest(std::vector<double> x1, std::vector<double> x2);

        // Move constructor   
        TTest(TTest && other) = default;

        // Move assignment operator   
        TTest& operator=(TTest && other) = default;

        // Copy constructor   
        TTest(const TTest & other) = default;

        // Copy assignment operator   
        TTest& operator=(const TTest & other) = default;

        // Default destruction
        virtual ~TTest() = default;

        // Perform the statistical test
        [[nodiscard]]
        bool Perform() override;

    private:
        // mu0 unknown population mean
        double m_mu0{ 0.0 };

        // sample mean
        double m_x_bar{ 0.0 };

        // sample standard deviation
        double m_sx{ 0.0 };

        // sample size
        double m_n{ 0.0 };

        // Sample 1
        std::vector<double> m_x1;

        // Sample 2
        std::vector<double> m_x2;

        // Test type
        TestType m_test_type{ TestType::Unknown };
    };

    // F-Test
    class STATSDLL_API FTest final : public StatisticalTest
    {
        enum class STATSDLL_API TestType { Unknown, FromData, TwoSample};

    public:
        // Summary data: sample std dev 1, sample std dev 2, sample size 1, sample size 2.
        FTest(double sx1, double sx2, double n1, double n2);

        // Two-sample
        FTest(std::vector<double> x1, std::vector<double> x2);

        // Move constructor   
        FTest(FTest&& other) = default;

        // Move assignment operator   
        FTest& operator=(FTest&& other) = default;

        // Copy constructor   
        FTest(const FTest& other) = default;

        // Copy assignment operator   
        FTest& operator=(const FTest & other) = default;

        // Default destruction
        virtual ~FTest() = default;

        // Perform the statistical test
        [[nodiscard]]
        bool Perform() override;

    private:
        // sample standard deviation 1
        double m_sx1{ 0.0 };

        // sample standard deviation 2
        double m_sx2{ 0.0 };

        // sample size 1
        double m_n1{ 0.0 };

        // sample size 2
        double m_n2{ 0.0 };

        // Sample 1
        std::vector<double> m_x1;

        // Sample 2
        std::vector<double> m_x2;

        // Test type
        TestType m_test_type{ TestType::Unknown };
    };

    // Z-Test
    class STATSDLL_API ZTest final : public StatisticalTest
    {
        enum class STATSDLL_API TestType { Unknown, OneSample, TwoSample, NoSample };

    public:
        // Summary data: population mean, sample mean, sample standard deviation, sample size.
        ZTest(double mu0, double x_bar, double sx, double n);

        // One-sample: population mean, sample.
        ZTest(double mu0, std::vector<double> x1);

        // Two-sample
        ZTest(std::vector<double> x1, std::vector<double> x2);

        // Move constructor   
        ZTest(ZTest&& other) = default;

        // Move assignment operator   
        ZTest& operator=(ZTest&& other) = default;

        // Copy constructor   
        ZTest(const ZTest& other) = default;

        // Copy assignment operator   
        ZTest& operator=(const ZTest& other) = default;

        // Default destruction
        virtual ~ZTest() = default;

        // Perform the statistical test
        [[nodiscard]]
        bool Perform() override;

    private:
        // mu0 unknown population mean
        double m_mu0{ 0.0 };

        // sample mean
        double m_x_bar{ 0.0 };

        // sample standard deviation
        double m_sx{ 0.0 };

        // sample size
        double m_n{ 0.0 };

        // Sample 1
        std::vector<double> m_x1;

        // Sample 2
        std::vector<double> m_x2;

        // Test type
        TestType m_test_type{ TestType::Unknown };
    };

    // One-way ANOVA test
    class STATSDLL_API ANOVA final : public StatisticalTest
    {
        enum class STATSDLL_API TestType { Unknown, OneWay };

    public:
        // 
        ANOVA(std::vector<double> x1, std::vector<double> x2, std::vector<double> x3);

        // Move constructor   
        ANOVA(ANOVA&& other) = default;

        // Move assignment operator   
        ANOVA& operator=(ANOVA&& other) = default;

        // Copy constructor   
        ANOVA(const ANOVA& other) = default;

        // Copy assignment operator   
        ANOVA& operator=(const ANOVA& other) = default;

        // Default destruction
        virtual ~ANOVA() = default;

        // Perform the statistical test
        [[nodiscard]]
        bool Perform() override;

    private:
        // Sample 1
        std::vector<double> m_x1;

        // Sample 2
        std::vector<double> m_x2;

        // Sample 3
        std::vector<double> m_x3;

        // Test type
        TestType m_test_type{ TestType::Unknown };
    };


}
