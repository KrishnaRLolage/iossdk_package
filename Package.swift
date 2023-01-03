// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "DragonMedicalSpeechKit",
    platforms: [.iOS(.v14)],
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "DragonMedicalSpeechKit",
            targets: ["DragonMedicalSpeechKit", "DragonMedicalSpeechKitBundle"]),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        
        .target(
            name: "DragonMedicalSpeechKitBundle",
            resources: [.copy("DragonMedicalSpeechKit.bundle")]
        ),
        .binaryTarget(
            name: "DragonMedicalSpeechKit",
            url: "https://github.com/ravindra-psc/iossdk_xcframework/raw/main/0.0.4.zip",
            checksum: "939b499b31242c65438621140743d96ef76d47c2be88bd6f183ee242fee782a5"
        )
    ]
)
