#include "DeferredTestReporter.h"
#include "TestDetails.h"
#include "Config.h"

using namespace UnitTest;

void DeferredTestReporter::ReportTestStart(TestDetails const& details)
{
    m_results.push_back(DeferredTestResult(details.suiteName, details.testName));
}

void DeferredTestReporter::ReportFailure(TestDetails const& details, char const* failure)
{
    DeferredTestResult& r = m_results.back();
    r.failed = true;
    r.failures.push_back(DeferredTestResult::Failure(details.lineNumber, failure));
    r.failureFile = details.filename;
}

void DeferredTestReporter::ReportTestFinish(TestDetails const&, float secondsElapsed)
{
    DeferredTestResult& r = m_results.back();
    r.timeElapsed = secondsElapsed;
}

DeferredTestReporter::DeferredTestResultList& DeferredTestReporter::GetResults()
{
    return m_results;
}
