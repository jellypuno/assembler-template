import defaultBindOptions from "./imports/bind/defaultBindOptions";
import dataSets from "./imports/dataSets";
import uploads from "./imports/uploads";
import assemblyOptions from "./imports/assembly/assemblyOptions";
import assemblyMaclibs from "./imports/assembly/assemblyMaclibs";
import metalOptions64 from "./imports/metal/metalOptions64";
import metalIncludes from "./imports/metal/metalIncludes";

export default {

    // settings for all other sections
    settings: {
        hlq: "PUBLIC.TEMPLATE"
    },

    // working data sets to allocate
    dataSets,

    // mapping local z/OS to LLQ data sets
    uploads,

    // job info
    job: {
        name: "TEMPLATE",
        account: "#ACCT",
        description: "ASM/BIND/RUN",

        // metal c compilations
        metalCompilations: [
            {
                name: "TEMPLATE",
                options: metalOptions64,
                includes: metalIncludes,
            }
        ],

        // assemblies
        assemblies: [
            {
                name: "TEMPLATE",
                options: assemblyOptions,
                maclibs: assemblyMaclibs,
            },
            {
                name: "WTOUTILS",
                options: assemblyOptions,
                maclibs: assemblyMaclibs,
            },
        ],

        // binds
        binds: [
            {
                name: "TEMPLATE",
                options: defaultBindOptions,
                includes: [
                    "WTOUTILS"
                ]
            }
        ],

        // executables
        execs: [
            {
                name: "TEMPLATE",
            }
        ]
    }
}