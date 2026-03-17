namespace MsaLab { namespace Details
{
  void TestLog(opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger>& logger,
    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer>& tracer);

  void TestTrace(opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger>& logger,
    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer>& tracer);
} // namespace Details
} // namespace MsaLab

