#!/bin/env python

import ROOT 

f=ROOT.TFile("data/muons/muon_tau.root")

h1=f.Get("NRecoTriggers1/1_Fraction_HTau1Pt")
h2=f.Get("NRecoTriggers1/2_Fraction_HTau1Pt")
h3=f.Get("NRecoTriggers1/3_Fraction_HTau1Pt")
h4=f.Get("NRecoTriggers1/4_Fraction_HTau1Pt")
h5=f.Get("NRecoTriggers1/5_Fraction_HTau1Pt")

l=[h1,h2,h3,h4,h5]


first=""
for h in l:
	h.Scale(1./h.Integral())
	h.Draw(first)
	first=" same"

raw_input()
