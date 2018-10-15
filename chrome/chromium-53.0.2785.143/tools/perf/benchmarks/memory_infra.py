# Copyright 2015 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import re

from core import perf_benchmark

from telemetry import benchmark
from telemetry.timeline import chrome_trace_category_filter
from telemetry.web_perf import timeline_based_measurement
from telemetry.web_perf.metrics import memory_timeline

import page_sets


# See tr.v.Numeric.getSummarizedScalarNumericsWithNames()
# https://github.com/catapult-project/catapult/blob/master/tracing/tracing/value/numeric.html#L323
_IGNORED_STATS_RE = re.compile(
    r'(?<!dump)(?<!process)_(std|count|max|min|sum|pct_\d{4}(_\d+)?)$')


class _MemoryInfra(perf_benchmark.PerfBenchmark):
  """Base class for new-generation memory benchmarks based on memory-infra.

  This benchmark records data using memory-infra (https://goo.gl/8tGc6O), which
  is part of chrome tracing, and extracts it using timeline-based measurements.
  """

  # Subclasses can override this to use TBMv2 instead of TBMv1.
  TBM_VERSION = 1

  def SetExtraBrowserOptions(self, options):
    options.AppendExtraBrowserArgs([
        # TODO(perezju): Temporary workaround to disable periodic memory dumps.
        # See: http://crbug.com/513692
        '--enable-memory-benchmarking',
    ])

  def CreateTimelineBasedMeasurementOptions(self):
    # Enable only memory-infra, to get memory dumps, and blink.console, to get
    # the timeline markers used for mapping threads to tabs.
    trace_memory = chrome_trace_category_filter.ChromeTraceCategoryFilter(
        filter_string='-*,blink.console,disabled-by-default-memory-infra')
    tbm_options = timeline_based_measurement.Options(
        overhead_level=trace_memory)
    tbm_options.config.enable_android_graphics_memtrack = True
    if self.TBM_VERSION == 1:
      # TBMv1 (see telemetry/telemetry/web_perf/metrics/memory_timeline.py
      # in third_party/catapult).
      tbm_options.SetLegacyTimelineBasedMetrics((
          memory_timeline.MemoryTimelineMetric(),
      ))
    elif self.TBM_VERSION == 2:
      # TBMv2 (see tracing/tracing/metrics/system_health/memory_metric.html
      # in third_party/catapult).
      tbm_options.SetTimelineBasedMetric('memoryMetric')
    else:
      raise Exception('Unrecognized TBM version: %s' % self.TBM_VERSION)
    return tbm_options


# TODO(bashi): Workaround for http://crbug.com/532075.
# @benchmark.Enabled('android') shouldn't be needed.
@benchmark.Enabled('android')
class MemoryBenchmarkTop10Mobile(_MemoryInfra):
  """Measure foreground/background memory on top 10 mobile page set.

  This metric provides memory measurements for the System Health Plan of
  Chrome on Android.
  """
  page_set = page_sets.MemoryTop10Mobile
  options = {'pageset_repeat': 5}

  @classmethod
  def Name(cls):
    return 'memory.top_10_mobile'

  @classmethod
  def ShouldDisable(cls, possible_browser):
    # Note: benchmark cannot be disabled with a decorator since, otherwise,
    # subclasses would also get disabled.
    return True


# TODO(bashi): Workaround for http://crbug.com/532075.
# @benchmark.Enabled('android') shouldn't be needed.
@benchmark.Enabled('android')
class TBMv2MemoryBenchmarkTop10Mobile(MemoryBenchmarkTop10Mobile):
  """Measure foreground/background memory on top 10 mobile page set (TBMv2).

  This is a temporary benchmark to compare the new TBMv2 memory metric
  (memory_metric.html) with the existing TBMv1 one (memory_timeline.py). Once
  all issues associated with the TBMv2 metric are resolved, all memory
  benchmarks (including the ones in this file) will switch to use it instead
  of the TBMv1 metric and this temporary benchmark will be removed. See
  crbug.com/60361.
  """
  TBM_VERSION = 2

  @classmethod
  def Name(cls):
    return 'memory.top_10_mobile_tbmv2'

  @classmethod
  def ShouldDisable(cls, possible_browser):
    # TODO(crbug.com/586148): Benchmark should not depend on DeskClock app.
    return not possible_browser.platform.CanLaunchApplication(
        'com.google.android.deskclock')

  @classmethod
  def ValueCanBeAddedPredicate(cls, value, is_first_result):
    # TODO(crbug.com/610962): Remove this stopgap when the perf dashboard
    # is able to cope with the data load generated by TBMv2 metrics.
    return not _IGNORED_STATS_RE.search(value.name)


# Benchmark disabled by default. Force to run with --also-run-disabled-tests.
@benchmark.Disabled('all')
class DualBrowserBenchmark(_MemoryInfra):
  """Measures memory usage while interacting with two different browsers.

  The user story involves going back and forth between doing Google searches
  on a webview-based browser (a stand in for the Search app), and loading
  pages on a select browser.
  """
  TBM_VERSION = 2
  page_set = page_sets.DualBrowserStorySet
  options = {'pageset_repeat': 5}

  @classmethod
  def Name(cls):
    return 'memory.dual_browser_test'

  @classmethod
  def ValueCanBeAddedPredicate(cls, value, is_first_result):
    # TODO(crbug.com/610962): Remove this stopgap when the perf dashboard
    # is able to cope with the data load generated by TBMv2 metrics.
    return not _IGNORED_STATS_RE.search(value.name)


# Benchmark disabled by default. Force to run with --also-run-disabled-tests.
@benchmark.Disabled('all')
class LongRunningDualBrowserBenchmark(_MemoryInfra):
  """Measures memory during prolonged usage of alternating browsers.

  Same as memory.dual_browser_test, but the test is run for 60 iterations
  and the browser is *not* restarted between page set repeats.
  """
  TBM_VERSION = 2
  page_set = page_sets.DualBrowserStorySet
  options = {'pageset_repeat': 60}

  @classmethod
  def Name(cls):
    return 'memory.long_running_dual_browser_test'

  @classmethod
  def ShouldTearDownStateAfterEachStorySetRun(cls):
    return False

  @classmethod
  def ValueCanBeAddedPredicate(cls, value, is_first_result):
    # TODO(crbug.com/610962): Remove this stopgap when the perf dashboard
    # is able to cope with the data load generated by TBMv2 metrics.
    return not _IGNORED_STATS_RE.search(value.name)


# TODO(bashi): Workaround for http://crbug.com/532075
# @benchmark.Enabled('android') shouldn't be needed.
@benchmark.Enabled('android')
class RendererMemoryBlinkMemoryMobile(_MemoryInfra):
  """Timeline based benchmark for measuring memory consumption on mobile
  sites on which blink's memory consumption is relatively high.
  """
  TBM_VERSION = 2

  page_set = page_sets.BlinkMemoryMobilePageSet

  def SetExtraBrowserOptions(self, options):
    super(RendererMemoryBlinkMemoryMobile, self).SetExtraBrowserOptions(
        options)
    options.AppendExtraBrowserArgs([
        # Ignore certs errors because record_wpr cannot handle certs correctly
        # in some cases (e.g. WordPress).
        '--ignore-certificate-errors',
    ])

  @classmethod
  def Name(cls):
    return 'memory.blink_memory_mobile'

  @classmethod
  def ValueCanBeAddedPredicate(cls, value, is_first_result):
    return (not _IGNORED_STATS_RE.search(value.name) and
            'renderer_processes' in value.name)


class _MemoryV8Benchmark(_MemoryInfra):

  # Report only V8-specific and overall renderer memory values. Note that
  # detailed values reported by the OS (such as native heap) are excluded.
  _V8_AND_OVERALL_MEMORY_RE = re.compile(
      r'renderer_processes:'
      r'(reported_by_chrome:v8|reported_by_os:system_memory:[^:]+$)')

  def CreateTimelineBasedMeasurementOptions(self):
    v8_categories = [
        'blink.console', 'renderer.scheduler', 'v8', 'webkit.console']
    memory_categories = ['blink.console', 'disabled-by-default-memory-infra']
    category_filter = chrome_trace_category_filter.ChromeTraceCategoryFilter(
        ','.join(['-*'] + v8_categories + memory_categories))
    options = timeline_based_measurement.Options(category_filter)
    options.SetTimelineBasedMetric('v8AndMemoryMetrics')
    return options

  @classmethod
  def ValueCanBeAddedPredicate(cls, value, _):
    if 'memory:chrome' in value.name:
      # TODO(petrcermak): Remove the first two cases once
      # https://codereview.chromium.org/2018503002/ lands in Catapult and rolls
      # into Chromium.
      return ('renderer:subsystem:v8' in value.name or
              'renderer:vmstats:overall' in value.name or
              bool(cls._V8_AND_OVERALL_MEMORY_RE.search(value.name)))
    return 'v8' in value.name


class MemoryLongRunningIdleGmail(_MemoryV8Benchmark):
  """Use (recorded) real world web sites and measure memory consumption
  of long running idle Gmail page """
  page_set = page_sets.LongRunningIdleGmailPageSet

  @classmethod
  def Name(cls):
    return 'memory.long_running_idle_gmail_tbmv2'

  @classmethod
  def ShouldDisable(cls, possible_browser):
    return cls.IsSvelte(possible_browser)  # http://crbug.com/611167


@benchmark.Enabled('has tabs')  # http://crbug.com/612210
class MemoryLongRunningIdleGmailBackground(_MemoryV8Benchmark):
  """Use (recorded) real world web sites and measure memory consumption
  of long running idle Gmail page """
  page_set = page_sets.LongRunningIdleGmailBackgroundPageSet

  @classmethod
  def Name(cls):
    return 'memory.long_running_idle_gmail_background_tbmv2'

  @classmethod
  def ShouldDisable(cls, possible_browser):  # http://crbug.com/616530
    return cls.IsSvelte(possible_browser)
