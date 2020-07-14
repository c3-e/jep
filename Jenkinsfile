def dockerRegistry = "artifacts.c3-e.com"
def internalRegistry = "https://${dockerRegistry}/"
def secureVault = "c3-devops-secure-vault"
def aws_creds_vault = "s3://${secureVault}/aws-creds.json"

def bucketConfigJson = "artifact-buckets-config.json"

def aws_creds = "AWS_ACCESS_KEY_ID=\$(aws s3 cp ${aws_creds_vault} - | jq -r '.AWS_ACCESS_KEY_ID')\nAWS_SECRET_ACCESS_KEY=\$(aws s3 cp ${aws_creds_vault} - | jq -r '.AWS_SECRET_ACCESS_KEY')"

def silent(cmd) {
    sh('#!/bin/sh -e\n' + cmd)
}

def dockerComposeCmd = "/usr/local/bin/docker-compose"

def dockerCompose(cmd, composeFile="main", returnStdout=false) {
    def dockerProjectId = "-p ${projectId}${env.JUPYTER_DEVTOOLS_IMAGE_NAME}"

    def scriptCmd = ["docker-compose"]
    if (composeFile != "main") {
        scriptCmd << "-f docker-compose-${composeFile}.yml"
        dockerProjectId += composeFile
    }
    scriptCmd << dockerProjectId
    scriptCmd << cmd
    scriptCmd = scriptCmd.join(" ")

    return sh(script: scriptCmd, returnStdout: returnStdout)
}

def dockerExec(cmd, composeFile="main", service="client", returnStdout=false) {
    return dockerCompose("exec -T ${service} " + cmd, composeFile, returnStdout)
}

def ensureDockerVolumeExists(volumeName) {
    sh "docker volume inspect ${volumeName} || docker volume create --name ${volumeName}"
}

node('docker-compose') {

    properties([
        disableConcurrentBuilds(),
        parameters([
            string(
                defaultValue: "artifacts.c3-e.com/c3-jupyter-devtools:minimal",
                description: 'c3 server docker image',
                name: 'JUPYTER_DEVTOOLS_IMAGE_NAME' // TODO PICK (OR MAKE) A BETTER DOCKER IMAGE
            ),
            booleanParam(
                defaultValue: false,
                description: 'Rebuild docker image to build conda package',
                name: 'CONDA_DOCKER_IMAGE_REBUILD'
            ),
            booleanParam(
                defaultValue: true,
                description: 'Publish to internal anaconda channel',
                name: 'CONDA_PUBLISH'
            )
        ])
    ])

    withEnv(["WORKSPACE=${pwd()}"]) {
        // enables fetch-tags, cf. https://issues.jenkins-ci.org/browse/JENKINS-45164
        checkout([
            $class: 'GitSCM',
            branches: scm.branches,
            extensions: [[$class: 'CloneOption', noTags: false, shallow: false, depth: 0, reference: '']],
            userRemoteConfigs: scm.userRemoteConfigs,
        ])

        // git short commit id
        gitCommit = sh(returnStdout: true, script: 'git rev-parse HEAD').trim().take(8)

        /*
         * The `projectId` is used to separate multiple container environments.
         */
        projectId = sh(returnStdout: true, script: "git describe").trim()
        currentBuild.description = "${projectId}"

        ansiColor('xterm') {
            // sane access to property `JUPYTER_DEVTOOLS_IMAGE_NAME`
            withEnv(["JUPYTER_DEVTOOLS_IMAGE_NAME=${params.JUPYTER_DEVTOOLS_IMAGE_NAME}"]) {

                try {
                    stage('preparation') {

                        // Ensure `docker-compose` is installed.
                        sh "${dockerComposeCmd} --version"

                        withAWS(region: 'us-east-1') {
                            s3Download(file: "tmp/${bucketConfigJson}", bucket: secureVault, path: "${bucketConfigJson}", force: true)
                        }

                        // Re-create tmp directory to store junit test results
                        sh "rm -rf tmp; mkdir tmp"

                        /*
                         * Set up environment that docker-compose will use.
                         * NOTE: The `.env` file follows a `VAR=VALUE` syntax.
                         */
                        // Add AWS credentials
                        silent "echo -e \"${aws_creds}\" > ${env.WORKSPACE}/.env"

                        docker.withRegistry(internalRegistry) {
                            dockerCompose "--version"

                            // Clean up any outdated state
                            dockerCompose "down --rmi all --remove-orphans"

                            if (params.CONDA_DOCKER_IMAGE_REBUILD) {
                                // Build build image
                                dockerCompose "build"
                                // Push updated build image
                                dockerCompose "push"
                            }

                            // Pull updated images
                            dockerCompose "pull"
                            // Create and start networks and containers
                            dockerCompose "up -d"
                            // Show general status information
                            dockerCompose "ps"
                            // Hide AWS credentials from being printed to screen
                            dockerCompose "config | grep -v \"AWS_\""
                        }
                    }

                    stage('build and publish') {
                        docker.withRegistry(internalRegistry) {

                            def publishSetting = params.CONDA_PUBLISH ? "yes" : "no"
                            dockerExec "conda config --set anaconda_upload ${publishSetting}"

                            // Build and publish `c3jep` package
                            dockerExec "/bin/sh -c \"conda build purge && conda build --no-copy-test-source-files .\""
                            dockerExec "/bin/sh -c \"mvn deploy .\""

                        }
                    }
                }

                catch (e) {
                    // Explicitly fail unless another result was already set
                    currentBuild.result = currentBuild.result ?: 'FAILURE'
                    throw e
                }

                finally {
                    stage('cleanup') {
                        dockerCompose "down --remove-orphans"

                    }
                }
            }
        }
    }
}