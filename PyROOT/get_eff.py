#!/bin/env python

import ROOT
#from rootpy.io import File



f=ROOT.TFile("test.root")


total=f.Get("NRecoTriggers1/GenTau_Matched_Pt")
passed=f.Get("NRecoTriggers1/GenTau_Matched_RecoPt")


teff=ROOT.TEfficiency(passed,total)
teff.Draw()

input("nknk")
