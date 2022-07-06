
#include "TRestGeant4PhysicsInfo.h"

#include <iostream>

using namespace std;

ClassImp(TRestGeant4PhysicsInfo);

set<TString> TRestGeant4PhysicsInfo::GetAllParticles() const {
    set<TString> particles = {};
    for (const auto& [_, name] : fParticleNamesMap) {
        particles.insert(name);
    }
    return particles;
}

std::set<TString> TRestGeant4PhysicsInfo::GetAllProcesses() const {
    set<TString> processes = {};
    for (const auto& [_, name] : fProcessNamesMap) {
        processes.insert(name);
    }
    return processes;
}

void TRestGeant4PhysicsInfo::PrintParticles() const {
    const auto particleNames = GetAllParticles();
    cout << "Particles:" << endl;
    for (const auto& name : particleNames) {
        const auto id = GetParticleID(name);
        cout << "\t" << name << " - " << id << endl;
    }
}

void TRestGeant4PhysicsInfo::PrintProcesses() const {
    const auto processNames = GetAllProcesses();
    cout << "Processes:" << endl;
    for (const auto& name : processNames) {
        const auto id = GetProcessID(name);
        cout << "\t" << name << " - " << id << endl;
    }
}

void TRestGeant4PhysicsInfo::Print() const {
    PrintParticles();
    PrintProcesses();
}

void TRestGeant4PhysicsInfo::InsertProcessName(Int_t id, const TString& processName) {
    fProcessNamesMap[id] = processName;
    fProcessNamesReverseMap[processName] = id;
}

void TRestGeant4PhysicsInfo::InsertParticleName(Int_t id, const TString& particleName) {
    fParticleNamesMap[id] = particleName;
    fParticleNamesReverseMap[particleName] = id;
}

template <typename T, typename U>
U GetOrDefaultMapValueFromKey(const map<T, U>* pMap, const T& key) {
    if (pMap->count(key) > 0) {
        return pMap->at(key);
    }
    return {};
}

TString TRestGeant4PhysicsInfo::GetProcessName(Int_t id) const {
    return GetOrDefaultMapValueFromKey<Int_t, TString>(&fProcessNamesMap, id);
}

Int_t TRestGeant4PhysicsInfo::GetProcessID(const TString& processName) const {
    return GetOrDefaultMapValueFromKey<TString, Int_t>(&fProcessNamesReverseMap, processName);
}

TString TRestGeant4PhysicsInfo::GetParticleName(Int_t id) const {
    return GetOrDefaultMapValueFromKey<Int_t, TString>(&fParticleNamesMap, id);
}

Int_t TRestGeant4PhysicsInfo::GetParticleID(const TString& processName) const {
    return GetOrDefaultMapValueFromKey<TString, Int_t>(&fParticleNamesReverseMap, processName);
}
