#!/usr/bin/env node
import * as cdk from 'aws-cdk-lib/core';
import { CdkProjectsStack } from '../lib/cdk-projects-stack';

const app = new cdk.App();
new CdkProjectsStack(app, 'CdkProjectsStack');
