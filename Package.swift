// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "DragonMedicalSpeechKit",
    defaultLocalization: "en",
    platforms: [
        .iOS(.v14)
        ],
    products: [
        // Products define the executables and libraries produced by a package, and make them visible to other packages.
        .library(
            name: "DragonMedicalSpeechKit",
            targets: ["DragonMedicalSpeechKitBundle", "DragonMedicalSpeechKit"]
        )
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages which this package depends on.
        .target(
            name: "DragonMedicalSpeechKitBundle",
            path: "Sources/SDK",
            resources: [
                .process("DragonMedicalSpeechKitBundle/Correction.storyboardc"),
                .process("DragonMedicalSpeechKitBundle/acmod6_6000_enu_gen_car_f16_v1_0_1.dat"),
                .process("DragonMedicalSpeechKitBundle/anyspeech.fcf"),
                .process("DragonMedicalSpeechKitBundle/cdd.bnf"),
                .process("DragonMedicalSpeechKitBundle/clc_enu_cfg3_v6_1_0.dat"),
                .process("DragonMedicalSpeechKitBundle/vocon3200_asr.dat"),
                .process("DragonMedicalSpeechKitBundle/wuw.fcf"),
            ]
        ),
        .binaryTarget(
                    name: "DragonMedicalSpeechKit",
                    path: "Sources/SDK/DragonMedicalSpeechKit.zip"
                )
    ]
)

//
