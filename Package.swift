// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "DragonMedicalSpeechKit",
    platforms: [
        .iOS(.v14)
        ],
    products: [
        // Products define the executables and libraries produced by a package, and make them visible to other packages.
        .library(
            name: "DragonMedicalSpeechKit",
            targets: ["DragonMedicalSpeechKit", "DragonMedicalSpeechKitBundle"]
        )
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages which this package depends on.
        .target(
            name: "DragonMedicalSpeechKitBundle",
            dependencies: [
                .target(name: "DragonMedicalSpeechKit"),
                .target(name: "opus")
            ],
            resources: [.copy("Resources/DragonMedicalSpeechKit.bundle")]
        ),
//        .binaryTarget(
//            name: "DragonMedicalSpeechKit",
//            url: "https://github.com/ravindra-psc/iossdk_xcframework/raw/main/0.0.4.zip",
//            checksum: "939b499b31242c65438621140743d96ef76d47c2be88bd6f183ee242fee782a5"
//        ),
        .binaryTarget(
                    name: "DragonMedicalSpeechKit",
                    path: "Sources/SDK/DragonMedicalSpeechKit.zip"
                ),
        .binaryTarget(
                    name: "opus",
                    path: "Sources/opus/opus.zip"
                ),
    ]
)

