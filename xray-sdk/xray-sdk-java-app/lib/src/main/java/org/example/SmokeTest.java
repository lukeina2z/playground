package org.example;

import com.amazonaws.xray.AWSXRayRecorder;


class SmokeTest {
    private AWSXRayRecorder xrayRecorder;

    public SmokeTest(AWSXRayRecorder recorder) {
        xrayRecorder = recorder;
    }

    void emits() {
        xrayRecorder.beginSubsegment("Smoke-Test-Segment");
        xrayRecorder.endSubsegment();
    }
}