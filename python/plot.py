#!/usr/bin/env python

import RandomHelper
import PlotHelper
import ROOT

mcPDF   = RandomHelper.BreitWigner(91.2,2)
dataPDF = RandomHelper.BreitWigner(89.2,4)

mc   = RandomHelper.GetRandom(mcPDF,   min = 81, max = 101, amount = 10000)
data = RandomHelper.GetRandom(dataPDF, min = 81, max = 101, amount = 10000)

mcHisto   = PlotHelper.ListToTH1D(mc, name="MC", Nbins=20)
dataHisto = PlotHelper.ListToTH1D(data, name="Data", Nbins=20)
dataHisto.SetLineColor(2)

mcHisto.SetLineWidth(3)
dataHisto.SetLineWidth(3)

canvas = ROOT.TCanvas("c1","c1" ,600,600)
canvas.cd()
colorlist = [ROOT.kAzure-6, ROOT.kGreen-2, ROOT.kOrange+1, ROOT.kAzure-4, ROOT.kGreen-9]
leg = ROOT.TLegend(0.8,0.8,0.92,0.92)
leg.AddEntry(mcHisto, "MC")
leg.AddEntry(dataHisto, "Data")

mcHisto.Draw("E")
dataHisto.Draw("Esame")
leg.Draw()

canvas.SaveAs("before.pdf")
